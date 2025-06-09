/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_executables.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:16:21 by fbicane           #+#    #+#             */
/*   Updated: 2025/06/05 13:19:12 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

void	ft_executable(t_shell *shell, pid_t pid, bool to_wait)
{
	char	**com;

	com = shell->cmd->u_as.exec.argv; // TODO: change to shell->c_exec
	if (0 == pid)
		setup_signals_child();

	if (('.' == com[0][0] && '/' == com[0][1]) || (ft_strchr(com[0], '/')) || ('/' == com[0][0])) // INFO: checks if the command is a path
		command_is_path(pid, shell, to_wait);
	else // INFO: need to look for command
		command_is_not_path(pid, shell, to_wait);
}
