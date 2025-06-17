/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 15:37:58 by fbicane           #+#    #+#             */
/*   Updated: 2025/06/16 14:39:53 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

void	set_pipes(t_pipes *pipe, t_shell *shell)
{
	pipe->pipex_to_free = NULL;
	creat_pipex(shell->cmd, &pipe->pipex_to_free);
	pipe->pipex = pipe->pipex_to_free;
	pipe->prev_pipe[0] = -1;
	pipe->prev_pipe[1] = -1;
	pipe->pids = NULL;
	shell->is_pipe = true;
	shell->pids = pipe->pids;
	shell->pipex = pipe->pipex_to_free;
}

void	pipes_parent_utils(t_pipes *pipes, t_shell *shell)
{
	if (-1 != pipes->prev_pipe[0])
		close(pipes->prev_pipe[0]);
	if (-1 != pipes->prev_pipe[1])
		close(pipes->prev_pipe[1]);
	if (pipes->pipex->next)
	{
		pipes->prev_pipe[0] = pipes->fd[0];
		pipes->prev_pipe[1] = pipes->fd[1];
	}
	increment_heredoc_pipe(shell, pipes->pipex);
}

void	is_pipe(t_shell *shell)
{
	t_pipes	pipes;

	set_pipes(&pipes, shell);
	while (pipes.pipex)
	{
		if (pipes.pipex->next)
		{
			if (-1 == pipe(pipes.fd))
				return (perror("pipe()"));
		}
		pipes.pid = fork();
		if (0 != pipes.pid)
			add_pid(&pipes.pids, pipes.pid);
		if (0 == pipes.pid)
			pipes_child_utils(&pipes, shell);
		else
			pipes_parent_utils(&pipes, shell);
		pipes.pipex = pipes.pipex->next;
	}
	wait_pids(&pipes.pids, shell);
	free_pipex(&pipes.pipex_to_free);
}
