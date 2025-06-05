/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:23:13 by fbicane           #+#    #+#             */
/*   Updated: 2025/06/05 16:23:33 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

void	is_redirection(t_shell *shell, bool to_fork, pid_t pid_r)
{
	t_cmd	*tmp;
	t_str_builder *sb;


	/*if (to_fork)*/
		/*ft_save_std_files(true);*/


	tmp = shell->cmd;
	sb = sb_create(10);
	if (sb == NULL)
		return;
	while (tmp != NULL && tmp->type == C_REDIRECT)
	{
		sb_append_str(sb, token_type_str(tmp->u_as.redirect.type), 0);
		sb_append_str(sb, tmp->u_as.redirect.file, 0);
		tmp = tmp->u_as.redirect.next;
	}
	char **redirects = sb_build(sb);

	if (!handle_redirections(redirects, shell))
	{
		shell->redirections_status = false;
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

	if (tmp)
	{
		// t_cmd *tmp2 = shell->cmd;
		shell->cmd = tmp;
		is_command(shell, to_fork,pid_r);
		// shell->cmd = tmp2;
	}
	if (to_fork)
		std_files(RESTORE_BOTH);
		/*ft_save_std_files(false);*/
}
