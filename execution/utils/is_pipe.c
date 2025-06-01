/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 15:37:58 by fbicane           #+#    #+#             */
/*   Updated: 2025/06/01 19:46:50 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

typedef struct s_pipex
{
	t_cmd			*cmd;
	struct s_pipex	*next;
}	t_pipex;

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
}


void	wait_pids(t_list *pids, t_shell *shell)
{
	pid_t	pid;

	while (pids)
	{
		pid = ft_atoi((char *)pids->content);
		waitpid(pid, NULL, 0);
		wait_child(pid, shell);
		pids = pids->next;
	}
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
	t_list	*pids = NULL;


	while(tmp)
	{

		if (tmp->next)
		{
			if (-1 == pipe(fd))
				return ; // TODO: error mssg
		}
		pid = fork();
		ft_lstadd_back(&pids, ft_lstnew(ft_itoa(pid))); // INFO: save all pids
		if (0 == pid)
		{
			if (-1 != prev_pipe[0]) // INFO: read from pipe if not first command
			{
				if (-1 == dup2(prev_pipe[0], STDIN_FILENO))
					return; // TODO: error mssg
			}
			if (tmp->next)
			{
				if (-1 == dup2(fd[1], STDOUT_FILENO))
					return; // TODO: error mssg
			}
			if (-1 != prev_pipe[0])
				close(prev_pipe[0]);
			if (-1 != prev_pipe[1])
				close(prev_pipe[1]);
			if (tmp->next)
			{
				close(fd[0]);
				close(fd[1]);
			}

			if (C_EXEC == tmp->cmd->type)
				is_command(shell, false, pid);
			if (C_REDIRECT == tmp->cmd->type)
				is_redirection(shell, false, pid);
			// TODO: execute the command
		}



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

	wait_pids(pids, shell); // TODO: check if it waits for pids
	free_pipex(&pipex);
}
