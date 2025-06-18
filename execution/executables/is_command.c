/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:23:44 by fbicane           #+#    #+#             */
/*   Updated: 2025/06/09 17:21:56 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

void	is_command_utils(struct stat *info, t_shell *shell)
{
	if (S_ISDIR(info->st_mode))
	{
		ft_printf(RED"%s: Is a directory\n"RESET,
			shell->cmd->u_as.exec.argv[0]);
		shell->exit_status = 126;
		return ;
	}
}

void	is_command(t_shell *shell, bool to_fork, pid_t pid_r)
{
	struct stat	info;

	if (false == shell->redirections_status)
	{
		shell->exit_status = 1;
		return ;
	}
	expand_params(&shell->cmd->u_as.exec.argv, shell);
	if (ft_is_builtin(shell->cmd->u_as.exec.argv[0]))
		run_bultins(shell);
	else
	{
		if (0 == stat(shell->cmd->u_as.exec.argv[0], &info))
			return (is_command_utils(&info, shell));
		else
		{
			if (to_fork)
				ft_apply_comm(shell, true, -3);
			else if (!to_fork)
				ft_apply_comm(shell, false, pid_r);
		}
	}
}
