/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 15:37:58 by fbicane           #+#    #+#             */
/*   Updated: 2025/06/05 14:49:48 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

t_pipex	*new_cmd_(t_cmd *cmd)
{
	t_pipex	*res;

	res = (t_pipex *)malloc(sizeof(t_pipex));
	if (!res)
		return (NULL);
	res->cmd = cmd;
	res->next = NULL;
	return (res);
}

void	append_cmd_(t_pipex **pipex, t_cmd *cmd)
{
	t_pipex	*tmp;

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

void	creat_pipex(t_cmd *cmd, t_pipex **pipex)
{
	if (C_PIPE == cmd->type)
		creat_pipex(cmd->u_as.pipe.left, pipex);
	if (C_EXEC == cmd->type || C_REDIRECT == cmd->type)
		append_cmd_(pipex, cmd);
	if (C_PIPE == cmd->type)
		append_cmd_(pipex, cmd->u_as.pipe.right);
}

void	free_pipex(t_pipex **pipex)
{
	t_pipex	*tmp;
	t_pipex	*to_free;

	tmp = (*pipex);
	while (tmp)
	{
		to_free = tmp;
		tmp = tmp->next;
		free(to_free);
	}
	(*pipex) = NULL;
}

void	is_pipe(t_shell *shell)
{
	t_pipex	*pipex = NULL;
	t_pipex	*tmp;

	creat_pipex(shell->cmd, &pipex);
	tmp = pipex;


	pid_t	pid;
	int		prev_pipe[2] = {-1, -1}; // INFO: hold pipes fds
	int		fd[2];
	t_wait_pids	*pids = NULL;


	shell->is_pipe = true;

	while(tmp)
	{

		if (tmp->next)
		{
			if (-1 == pipe(fd))
				return ; // TODO: error mssg
		}
		shell->pipe = shell->cmd;
		shell->pids = pids;
		shell->pipex = pipex;
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
			if (tmp->next)
			{
				if (-1 == dup2(fd[1], STDOUT_FILENO))
					exit(1); // TODO: error mssg
			}
			// Child process - only close the unused pipe end
			if (-1 != prev_pipe[0])
				close(prev_pipe[0]);
			if (-1 != prev_pipe[1])
				close(prev_pipe[1]);
			if (tmp->next)
			{
				close(fd[0]);  // Close read end in writing process
				// DON'T close fd[1] - you're writing to it!
			}
			else if (prev_pipe[0] != -1)
			{
				close(fd[1]);  // Close write end in reading process  
				// DON'T close fd[0] - you're reading from it!
			}

			    // Execute command
			// t_cmd *parent = shell->cmd;
			shell->cmd = tmp->cmd;
			if (C_EXEC == tmp->cmd->type)
				is_command(shell, false, pid);
			else if (C_REDIRECT == tmp->cmd->type)
				is_redirection(shell, false, pid);
			ft_putstr_fd("ana hnaya ma hrjtch\n", 2);
			/*close(fd[1]);*/
			// WARNING: see this case it changes it sends output to pipe maybe
				/*====> <<s | wc*/
				/*asdsds*/
				/*s*/
				/*ana hnaya ma hrjtch*/
				/*2       8      41*/
				/*the exit status : 0*/
				/*the exit status : 0*/
				/*====>*/

			// Child exits after command execution
			// if (pids)
			// 	free_pids(&pids);
			free_pipex(&pipex);
			ast_free(shell->root_to_free);
			exit(shell->exit_status);
		}
		/*t_cmd *parent = shell->cmd;*/
		/*shell->cmd = tmp->cmd;*/
		/*if (C_EXEC == tmp->cmd->type)*/
		/*{*/
		/*	is_command(shell, false, pid);*/
		/*	if (0 == pid)*/
		/*	{*/
		/*		free_pids(&pids);*/
		/*		free_pipex(&pipex);*/
		/*		ast_free(parent);*/
		/*		exit(shell->exit_status);*/
		/*	}*/
		/*	shell->cmd = parent;*/
		/*}*/
		/*else if (C_REDIRECT == tmp->cmd->type)*/
		/*{*/
		/*	is_redirection(shell, false, pid);*/
		/*	if (0 == pid)*/
		/*	{*/
		/*		free_pids(&pids);*/
		/*		free_pipex(&pipex);*/
		/*		ast_free(parent);*/
		/*		exit(shell->exit_status);*/
		/*	}*/
		/*	shell->cmd = parent;*/
		/*}*/
		// TODO: execute the command

		else
		{
			if (-1 != prev_pipe[0])
				close(prev_pipe[0]);
			if (-1 != prev_pipe[1])
				close(prev_pipe[1]);

			if (tmp->next)
			{
				prev_pipe[0] = fd[0];
				prev_pipe[1] = fd[1];
			}
		}
		tmp = tmp->next;
	}

	wait_pids(&pids, shell); // TODO: check if it waits for pids
	free_pipex(&pipex);
}
