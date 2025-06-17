/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_executable_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 12:02:30 by fbicane           #+#    #+#             */
/*   Updated: 2025/06/16 11:07:15 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

static void	command_is_path_utils(t_shell *shell, pid_t pid,
	bool to_wait, char **prep_envp)
{
	char	**com;

	com = shell->cmd->u_as.exec.argv;
	if (0 == pid)
	{
		prep_envp = ft_prep_envp(shell);
		execve(com[0], com, prep_envp);
		if (to_wait)
			executable_error(shell, 1, prep_envp);
		return (executable_error(shell, 2, prep_envp));
	}
	else if ((0 != pid) && to_wait)
		wait_child(pid, shell);
}

void	command_is_path(pid_t pid, t_shell *shell, bool to_wait)
{
	char	**com;
	char	**prep_envp;

	com = shell->cmd->u_as.exec.argv;
	prep_envp = NULL;
	if (!access(com[0], F_OK | X_OK))
		command_is_path_utils(shell, pid, to_wait, prep_envp);
	else
	{
		if (0 == pid)
		{
			if (to_wait)
				executable_error(shell, 3, prep_envp);
			return (executable_error_2(shell, 4));
		}
		else
		{
			if (to_wait)
				return (executable_error_2(shell, 5));
			return (executable_error_2(shell, 6));
		}
	}
}
