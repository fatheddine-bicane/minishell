/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_executables.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:16:21 by fbicane           #+#    #+#             */
/*   Updated: 2025/06/16 11:09:30 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

void	ft_executable(t_shell *shell, pid_t pid, bool to_wait)
{
	char	**com;

	com = shell->cmd->u_as.exec.argv;
	if (0 == pid)
		setup_signals_child();
	if (('.' == com[0][0] && '/' == com[0][1])
		|| (ft_strchr(com[0], '/')) || ('/' == com[0][0]))
		command_is_path(pid, shell, to_wait);
	else
		command_is_not_path(pid, shell, to_wait);
}
