/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:23:13 by fbicane           #+#    #+#             */
/*   Updated: 2025/06/16 15:27:55 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

static void	is_redirect_utils(t_shell *shell, bool to_fork, pid_t pid_r)
{
	if (NULL == shell->cmd)
	{
		if (to_fork)
			std_files(RESTORE_BOTH);
		return ;
	}
	if (C_EXEC == shell->cmd->type)
		is_command(shell, to_fork, pid_r);
	else if (C_GROUP == shell->cmd->type)
		is_group(shell);
	if (to_fork)
		std_files(RESTORE_BOTH);
}

static void	redirections_faild(t_shell *shell, char **redirects)
{
	shell->redirections_status = false;
	if (NULL != shell->heredocs_files)
	{
		ft_free_arr(shell->heredocs_files);
		shell->heredocs_files = NULL;
	}
	sn_strs_free(redirects);
	std_files(RESTORE_BOTH);
}

void	is_redirection(t_shell *shell, bool to_fork, pid_t pid_r)
{
	t_str_builder	*sb;
	char			**redirects;

	sb = sb_create(10);
	if (sb == NULL)
		return ;
	while (NULL != shell->cmd && C_REDIRECT == shell->cmd->type)
	{
		sb_append_str(sb, token_type_str(shell->cmd->u_as.redirect.type), 0);
		sb_append_str(sb, shell->cmd->u_as.redirect.file, 0);
		shell->cmd = shell->cmd->u_as.redirect.next;
	}
	redirects = sb_build(sb);
	if (!handle_redirections(redirects, shell))
	{
		redirections_faild(shell, redirects);
		return ;
	}
	sn_strs_free(redirects);
	is_redirect_utils(shell, to_fork, pid_r);
}
