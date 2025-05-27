/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:15:18 by fbicane           #+#    #+#             */
/*   Updated: 2025/05/13 16:48:09 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

void	ft_apply_comm(char *rl, t_list *my_envp, int *exit_stat)
{
	pid_t	pid;

	// INFO: ignore the signals in the parrent so the ctrl c wont quit the shell
	ignore_signals_parrent();
	pid = fork();
	if (-1 == pid)
	{
		// TODO: error mssg
	}
	ft_executable(rl, my_envp, pid, true, exit_stat);
	setup_signals();
}
