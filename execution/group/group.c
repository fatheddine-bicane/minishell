/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 12:43:32 by fbicane           #+#    #+#             */
/*   Updated: 2025/06/11 23:28:49 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

static void	is_group_utils(t_shell *shell)
{
	if (NULL != shell->heredocs_files)
	{
		ft_free_arr(shell->heredocs_files);
		shell->heredocs_files = NULL;
	}
}

static void	is_group_utils2(t_shell *shell)
{
	if (C_PIPE == shell->cmd->u_as.group.cmd->type)
	{
		shell->cmd = shell->cmd->u_as.group.cmd;
		is_pipe(shell);
		is_group_utils(shell);
	}
	else if (C_GROUP == shell->cmd->u_as.group.cmd->type)
	{
		shell->cmd = shell->cmd->u_as.group.cmd;
		is_group(shell);
	}
	else if (C_COMPOUND == shell->cmd->u_as.group.cmd->type)
	{
		shell->cmd = shell->cmd->u_as.group.cmd;
		is_compound(shell);
	}
}

void	is_group(t_shell *shell)
{
	pid_t	pid;

	shell->is_group = true;
	pid = fork();
	if (0 == pid)
	{
		if (C_EXEC == shell->cmd->u_as.group.cmd->type)
		{
			shell->cmd = shell->cmd->u_as.group.cmd;
			is_command(shell, true, -1);
		}
		else if (C_REDIRECT == shell->cmd->u_as.group.cmd->type)
		{
			shell->cmd = shell->cmd->u_as.group.cmd;
			is_redirection(shell, true, -1);
			is_group_utils(shell);
		}
		else
			is_group_utils2(shell);
		free_my_envp(&shell->my_envp);
		ast_free(shell->root_to_free);
		exit(shell->exit_status);
	}
	else if (0 != pid)
		wait_child(pid, shell);
}
