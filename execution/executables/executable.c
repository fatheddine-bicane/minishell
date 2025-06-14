/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:15:18 by fbicane           #+#    #+#             */
/*   Updated: 2025/06/05 13:11:32 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

void	ft_apply_comm(t_shell *shell, bool to_fork, pid_t pid_r)
{
	pid_t	pid;

	ignore_signals_parrent();// INFO: ignore the signals in the parrent so the ctrl c wont quit the shell



	// NOTE: if we executin a C_EXEC (we r not in pipe)
	if (to_fork)
	{
		pid = fork();
		if (-1 == pid)
		{
			// TODO: error mssg
		}
		ft_executable(shell, pid, true);
	}
	else
	{
		/*pid = pid_r*/
		/*if (-1 == pid)*/
		/*{*/
		/*	// TODO: error mssg*/
		/*}*/
		ft_executable(shell, pid_r, false);
	}
	setup_signals();
}
