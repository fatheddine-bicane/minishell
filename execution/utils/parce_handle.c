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
{
	if (ft_is_builtin(cmd->u_as.exec.argv[0]))
	{
		run_bultins(cmd->u_as.exec.argv, my_envp, exit_stat);
	}
	else
	{
		ft_apply_comm(cmd->u_as.exec.argv, *my_envp, exit_stat);
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

void	ft_save_std_files(bool save)
{
	static int	std_in_save;
	static int	std_out_save;

	if (true == save)
	{
		std_in_save = dup(STDIN_FILENO);
		if (-1 == std_in_save)
			return ; // TODO: error mssg
		int	std_out_save = dup(STDOUT_FILENO);
		if (-1 == std_out_save)
			return ; // TODO: error mssg
	}
	else
	{
		dup2(std_in_save, STDIN_FILENO);
		dup2(std_out_save, STDOUT_FILENO);
	}
}

void	is_redirection(t_cmd *cmd, t_list **my_envp, int *exit_stat)
{
	t_cmd	*tmp;
	t_str_builder *sb;


	ft_save_std_files(true);


	tmp = cmd;
	sb = sb_create(10);
	if (sb == NULL)
		return;
	/*[">" "file" "<" "file"] ["> file", "< file"]*/
	while (tmp != NULL && tmp->type == C_REDIRECT)
	{
		sb_append_str(sb, token_type_str(tmp->u_as.redirect.type), 0);
		sb_append_str(sb, tmp->u_as.redirect.file, 0);
		sb_append_char(sb, ' ');
		tmp = tmp->u_as.redirect.next;
	}
	char *redirects = sb_build(sb);// TODO: wait for karim merge for ** support


	ft_handle_redirections(ft_split(redirects, 32));

	if (tmp)
	{
		is_command(tmp, my_envp, exit_stat);
	}


	ft_save_std_files(false);
}

