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

	ignore_signals_parrent();
	if (to_fork)
	{
		pid = fork();
		if (-1 == pid)
			return (perror("fork()"));
		ft_executable(shell, pid, true);
	}
	else
		ft_executable(shell, pid_r, false);
	setup_signals();
}
