/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 15:37:58 by fbicane           #+#    #+#             */
/*   Updated: 2025/06/11 23:28:32 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

t_pipex *new_cmd_(t_cmd *cmd)
{
	t_pipex *res;

	res = (t_pipex *)malloc(sizeof(t_pipex));
	if (!res)
		return (NULL);
	res->cmd = cmd;
	res->next = NULL;
	return (res);
}

void append_cmd_(t_pipex **pipex, t_cmd *cmd)
{
	t_pipex *tmp;

	if (!(*pipex))
		(*pipex) = new_cmd_(cmd);
	else
	{
		tmp = (*pipex);
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_cmd_(cmd);
	}
}

void creat_pipex(t_cmd *cmd, t_pipex **pipex)
{
	if (C_PIPE == cmd->type)
		creat_pipex(cmd->u_as.pipe.left, pipex);
	if (C_EXEC == cmd->type || C_REDIRECT == cmd->type || C_GROUP == cmd->type)
		append_cmd_(pipex, cmd);
	if (C_PIPE == cmd->type)
		append_cmd_(pipex, cmd->u_as.pipe.right);
}

void free_pipex(t_pipex **pipex)
{
	if (!pipex || !*pipex)
		return;
	t_pipex *tmp;
	t_pipex *to_free;

	tmp = (*pipex);
	while (tmp)
	{
		to_free = tmp;
		tmp = tmp->next;
		free(to_free);
	}
	(*pipex) = NULL;
}

void	increment_heredoc_pipe(t_shell *shell, t_pipex *tmp)
{
	if (C_REDIRECT == tmp->cmd->type)
	{
		while (tmp->cmd)
		{
			if (C_REDIRECT != tmp->cmd->type)
				break ;
			if (T_HEREDOC == tmp->cmd->u_as.redirect.type)
				shell->herdocs_index++;
			tmp->cmd = tmp->cmd->u_as.redirect.next;
		}
	}
	else if (C_GROUP == tmp->cmd->type)
	{
		tmp->cmd = tmp->cmd->u_as.group.cmd;
		increment_heredoc_pipe(shell, tmp);
		/*if (C_PIPE == tmp->cmd->type)*/
		/*{*/
		/*	increment_heredoc_pipe(shell, tmp);*/
		/*}*/
		/*else if (C_REDIRECT == tmp->cmd->u_as.group.cmd->type)*/
		/*{*/
		/*}*/
	}
}

/*void	increment_heredoc_pipe(t_shell *shell, t_pipex *tmp)*/
/*{*/
/*	if (tmp && tmp->cmd)*/
/*		increment_heredoc_index(shell, tmp->cmd);*/
/*}*/


void is_pipe(t_shell *shell)
{
	t_pipex *pipex = NULL;
	t_pipex *tmp_pipex;

	creat_pipex(shell->cmd, &pipex);
	tmp_pipex = pipex;

	pid_t pid;
	int prev_pipe[2] = {-1, -1}; // INFO: hold pipes fds
	int fd[2];
	t_wait_pids *pids = NULL;

	shell->is_pipe = true;

	shell->pids = pids;
	shell->pipex = pipex;
	while (tmp_pipex)
	{

		if (tmp_pipex->next)
		{
			if (-1 == pipe(fd))
				return; // TODO: error mssg
		}
		/*shell->pipe = shell->cmd;*/
		pid = fork();
		if (0 != pid)
			add_pid(&pids, pid);
		if (0 == pid)
		{
			// WARNING: might be invalid free
			free_pids(&pids);
			if (-1 != prev_pipe[0]) // INFO: read from pipe if not first command
			{
				if (-1 == dup2(prev_pipe[0], STDIN_FILENO))
					exit(1); // TODO: error mssg
			}
			if (tmp_pipex->next)
			{
				if (-1 == dup2(fd[1], STDOUT_FILENO))
					exit(1); // TODO: error mssg
			}
			// Child process - only close the unused pipe end
			if (-1 != prev_pipe[0])
				close(prev_pipe[0]);
			if (-1 != prev_pipe[1])
				close(prev_pipe[1]);
			if (tmp_pipex->next)
				close(fd[0]); // Close read end in writing process
			else if (prev_pipe[0] != -1)
				close(fd[1]); // Close write end in reading process

			// NOTE: execute command
			shell->cmd = tmp_pipex->cmd;
			if (C_EXEC == tmp_pipex->cmd->type)
				is_command(shell, false, pid);
			else if (C_REDIRECT == tmp_pipex->cmd->type)
			{
				// WARNING: if the command contain a heredoc the herdoc index get
				// incremented in the child process not the main so the next child
				// will use the heredocindex and it will still be 0
				is_redirection(shell, false, pid);
			}
			else if (C_GROUP == tmp_pipex->cmd->type)
			{
				if (NULL != pipex)
					free_pipex(&pipex);
				is_group(shell);
				/*ft_putstr_fd(RED"group failed\n"RESET, 2);*/
			}



			// NOTE: childe failed to execute command
			/*ft_putstr_fd("ana hnaya ma hrjtch\n", 2);*/
			free_my_envp(&shell->my_envp); // WARNING : invalide free if mixed pipes and subshell and one of subshells pipes command is wrong
			free_pipex(&pipex);
			ft_free_arr(shell->heredocs_files);
			ast_free(shell->root_to_free);
			exit(shell->exit_status);
		}
		// TODO: execute the command

		else
		{
			if (-1 != prev_pipe[0])
				close(prev_pipe[0]);
			if (-1 != prev_pipe[1])
				close(prev_pipe[1]);

			if (tmp_pipex->next)
			{
				prev_pipe[0] = fd[0];
				prev_pipe[1] = fd[1];
			}
			/*increment_heredoc_index(shell, tmp->cmd);*/
			increment_heredoc_pipe(shell, tmp_pipex);
			/*printf("heredoc_index %d\n", shell->herdocs_index);*/
			/*increment_heredoc_pipe(shell, tmp);*/
		}
		tmp_pipex = tmp_pipex->next;
	}

	wait_pids(&pids, shell); 
	free_pipex(&pipex);
}
