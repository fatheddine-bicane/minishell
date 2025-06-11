/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:23:13 by fbicane           #+#    #+#             */
/*   Updated: 2025/06/11 17:35:29 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

void	is_redirection(t_shell *shell, bool to_fork, pid_t pid_r)
{
	/*t_cmd	*tmp;*/
	t_str_builder *sb;

	sb = sb_create(10);
	if (sb == NULL)
		return;
	while (NULL != shell->cmd && C_REDIRECT == shell->cmd->type)
	{
		sb_append_str(sb, token_type_str(shell->cmd->u_as.redirect.type), 0);
		sb_append_str(sb, shell->cmd->u_as.redirect.file, 0);
		shell->cmd = shell->cmd->u_as.redirect.next;
	}
	char **redirects = sb_build(sb);

	if (!handle_redirections(redirects, shell))
	{
		shell->redirections_status = false;
		ft_free_arr(shell->heredocs_files);
		sn_strs_free(redirects);
		if (0 == pid_r && !to_fork)
		{
			free_my_envp(&shell->my_envp);
			/*exit(shell->exit_status);*/
		}
		/*if (to_fork)*/
		std_files(RESTORE_BOTH);
			/*ft_save_std_files(false);*/
		return ;
	}
	sn_strs_free(redirects);

	if (NULL == shell->cmd)
	{
		if (to_fork)
			std_files(RESTORE_BOTH);
		return ;
	}

	if (C_EXEC == shell->cmd->type)
	{
		is_command(shell, to_fork,pid_r);
	}
	else if (C_GROUP == shell->cmd->type)
	{
		is_group(shell);
	}
	if (to_fork)
		std_files(RESTORE_BOTH);
		/*ft_save_std_files(false);*/
}
