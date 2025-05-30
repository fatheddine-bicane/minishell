/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 13:43:15 by fbicane           #+#    #+#             */
/*   Updated: 2025/05/29 16:52:57 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

void	is_command(t_cmd *cmd, t_list **my_envp, int *exit_stat)
/*void	is_command(t_shell *shell)*/
{
	if (ft_is_builtin(cmd->u_as.exec.argv[0]))
	{
		run_bultins(cmd->u_as.exec.argv, my_envp, exit_stat);
		/*run_bultins(shell);*/
	}
	else
	{
		ft_apply_comm(cmd->u_as.exec.argv, my_envp, exit_stat);
	}
}

/*void	is_pipe(t_cmd *cmd, t_list **my_envp, int *exit_stat)*/
/*{*/
/*t_cmd *tmp;*/
/**/
  /*is_redirect(cmd);*/
/*  tmp = cmd->u_as.redirect.next;*/
/*  if (tmp == NULL)*/
/*	  return;*/
/*  while (tmp != NULL)*/
/*  {*/
/*	  if (tmp->type == C_REDIRECT) {*/
/**/
/*	  }*/
/*	  tmp = cmd->u_as.redirect.next;*/
/*  }*/
/**/
	 /*ft_pipex(cmd->u_as.redirect.type == T_HEREDOC)*/
	 /* cmd->u_as.redirect.next->type*/
/*}*/

void	is_redirection(t_cmd *cmd, t_list **my_envp, int *exit_stat)
{
	t_cmd	*tmp;
	t_str_builder *sb;


	ft_save_std_files(true);


	tmp = cmd;
	sb = sb_create(10);
	if (sb == NULL)
		return;
	/*[">", "file", '' "<" "file"] ["> file", "< file"]*/
	while (tmp != NULL && tmp->type == C_REDIRECT)
	{
		sb_append_str(sb, token_type_str(tmp->u_as.redirect.type), 0);
		sb_append_str(sb, tmp->u_as.redirect.file, 0);
		tmp = tmp->u_as.redirect.next;
	}
	char **redirects = sb_build(sb);// TODO: wait for karim merge for ** support

	ft_handle_redirections(redirects);
	sn_strs_free(redirects);

	if (tmp)
	{
		is_command(tmp, my_envp, exit_stat);
	}
	ft_save_std_files(false);
}

