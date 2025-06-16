/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_pipe_child_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 14:22:29 by fbicane           #+#    #+#             */
/*   Updated: 2025/06/16 14:26:21 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

static void	utils_1(t_pipes *pipes)
{
	free_pids(&pipes->pids);
	if (-1 != pipes->prev_pipe[0]) // INFO: read from pipe if not first command
	{
		if (-1 == dup2(pipes->prev_pipe[0], STDIN_FILENO))
			return (perror("dup2()"), exit(1));
	}
	if (pipes->pipex->next)
	{
		if (-1 == dup2(pipes->fd[1], STDOUT_FILENO))
			return (perror("dup2()"), exit(1));
	}
	if (-1 != pipes->prev_pipe[0])
		close(pipes->prev_pipe[0]);
	if (-1 != pipes->prev_pipe[1])
		close(pipes->prev_pipe[1]);
	// NOTE: close read end in writing process
	if (pipes->pipex->next)
		close(pipes->fd[0]);
	// NOTE: close write end in reading process
	else if (pipes->prev_pipe[0] != -1)
		close(pipes->fd[1]);
}

void	pipes_child_utils(t_pipes *pipes, t_shell *shell)
{
	utils_1(pipes);
	// NOTE: execute command
	shell->cmd = pipes->pipex->cmd;
	if (C_EXEC == pipes->pipex->cmd->type)
	{
		is_command(shell, false, pipes->pid);
	}
	else if (C_REDIRECT == pipes->pipex->cmd->type)
	{
		is_redirection(shell, false, pipes->pid);
	}
	else if (C_GROUP == pipes->pipex->cmd->type)
	{
		if (NULL != pipes->pipex_to_free)
			free_pipex(&pipes->pipex_to_free);
		is_group(shell);
		ft_free_arr(shell->heredocs_files);
	}
	// NOTE: childe failed to execute command
	free_my_envp(&shell->my_envp);
	free_pipex(&pipes->pipex_to_free);
	ast_free(shell->root_to_free);
	exit(shell->exit_status);
}
