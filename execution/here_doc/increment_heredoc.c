/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   increment_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 12:29:00 by fbicane           #+#    #+#             */
/*   Updated: 2025/06/11 12:31:58 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

void	increment_heredoc_index(t_shell *shell, t_cmd *cmd)
{
	t_cmd *redirect_cmd;
	t_pipex *inner_pipex;
	t_pipex *tmp_pipex;

	if (!cmd)
		return;

	if (C_REDIRECT == cmd->type)
	{
		// Handle redirect commands - traverse the redirect chain
		redirect_cmd = cmd;
		while (redirect_cmd)
		{
			if (T_HEREDOC == redirect_cmd->u_as.redirect.type)
				shell->herdocs_index++;
			redirect_cmd = redirect_cmd->u_as.redirect.next;
		}
	}
	else if (C_PIPE == cmd->type)
	{
		// Handle pipe commands - create pipex and traverse all commands
		inner_pipex = NULL;
		creat_pipex(cmd, &inner_pipex);
		tmp_pipex = inner_pipex;

		while (tmp_pipex)
		{
			increment_heredoc_index(shell, tmp_pipex->cmd);
			tmp_pipex = tmp_pipex->next;
		}

		free_pipex(&inner_pipex);
	}
	else if (C_GROUP == cmd->type)
	{
		// Handle group commands - recurse into the grouped command
		increment_heredoc_index(shell, cmd->u_as.group.cmd);
	}
	else if (C_COMPOUND == cmd->type)
	{
		// Handle compound commands - recurse into both left and right
		increment_heredoc_index(shell, cmd->u_as.compound.left);
		increment_heredoc_index(shell, cmd->u_as.compound.right);
	}
	// C_EXEC commands don't contain heredocs, so we ignore them
}

// Simplified wrapper for pipex nodes
/*void	increment_heredoc_pipe(t_shell *shell, t_pipex *tmp)*/
/*{*/
/*	if (tmp && tmp->cmd)*/
/*		increment_heredoc_index(shell, tmp->cmd);*/
/*}*/
