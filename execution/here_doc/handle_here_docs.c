/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_here_docs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:19:34 by fbicane           #+#    #+#             */
/*   Updated: 2025/06/16 11:52:44 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

void	creat_heredoc_command(t_shell *shell, t_str_builder **sb)
{
	t_cmd	*tmp_cmd;

	tmp_cmd = shell->cmd;
	while (tmp_cmd)
	{
		if (C_REDIRECT != tmp_cmd->type)
			break ;
		if (T_HEREDOC == tmp_cmd->u_as.redirect.type)
		{
			sb_append_str((*sb), tmp_cmd->u_as.redirect.file, 0);
		}
		tmp_cmd = tmp_cmd->u_as.redirect.next;
	}
}

void	creat_heredoc_pipe(t_shell *shell, t_str_builder **sb)
{
	t_pipex	*pipex;
	t_pipex	*pipex_to_free;

	pipex = NULL;
	creat_pipex(shell->cmd, &pipex);
	pipex_to_free = pipex;
	while (pipex)
	{
		shell->cmd = pipex->cmd;
		if (C_REDIRECT == shell->cmd->type)
			creat_heredoc_command(shell, sb);
		else if (C_GROUP == shell->cmd->type)
			creat_heredoc_group(shell, sb);
		pipex = pipex->next;
	}
	free_pipex(&pipex_to_free);
}

void	creat_heredoc_compound(t_shell *shell, t_str_builder **sb)
{
	t_cmd	*tmp;
	t_cmd	*original_cmd;

	original_cmd = shell->cmd;
	tmp = shell->cmd->u_as.compound.left;
	shell->cmd = tmp;
	if (C_REDIRECT == tmp->type)
		creat_heredoc_command(shell, sb);
	else if (C_PIPE == tmp->type)
		creat_heredoc_pipe(shell, sb);
	else if (C_COMPOUND == tmp->type)
		creat_heredoc_compound(shell, sb);
	else if (C_GROUP == shell->cmd->type)
		creat_heredoc_group(shell, sb);
	shell->cmd = original_cmd;
	tmp = shell->cmd->u_as.compound.right;
	shell->cmd = tmp;
	if (C_REDIRECT == tmp->type)
		creat_heredoc_command(shell, sb);
	else if (C_PIPE == tmp->type)
		creat_heredoc_pipe(shell, sb);
	else if (C_GROUP == shell->cmd->type)
		creat_heredoc_group(shell, sb);
	shell->cmd = original_cmd;
}

void	creat_heredoc_group(t_shell *shell, t_str_builder **sb)
{
	t_cmd	*original_cmd;

	original_cmd = shell->cmd;
	shell->cmd = shell->cmd->u_as.group.cmd;
	if (C_REDIRECT == shell->cmd->type)
	{
		creat_heredoc_command(shell, sb);
	}
	else if (C_PIPE == shell->cmd->type)
	{
		creat_heredoc_pipe(shell, sb);
	}
	else if (C_COMPOUND == shell->cmd->type)
	{
		creat_heredoc_compound(shell, sb);
	}
	else if (C_GROUP == shell->cmd->type)
		creat_heredoc_group(shell, sb);
	shell->cmd = original_cmd;
}

// INFO: extract the heredocs delimiters
void	herdocs_delemiters(t_shell *shell)
{
	t_str_builder	*sb;
	char			**heredoc_delemiters;

	sb = sb_create(10);
	if (sb == NULL)
		return ;
	if (C_REDIRECT == shell->cmd->type)
		creat_heredoc_command(shell, &sb);
	else if (C_PIPE == shell->cmd->type)
		creat_heredoc_pipe(shell, &sb);
	else if (C_COMPOUND == shell->cmd->type)
		creat_heredoc_compound(shell, &sb);
	else if (C_GROUP == shell->cmd->type)
		creat_heredoc_group(shell, &sb);
	shell->cmd = shell->root_to_free;
	heredoc_delemiters = sb_build(sb);
	if (NULL == heredoc_delemiters)
	{
		shell->cmd = shell->root_to_free;
		shell->heredocs_delemiters = NULL;
		return ;
	}
	shell->heredocs_delemiters = heredoc_delemiters;
}
