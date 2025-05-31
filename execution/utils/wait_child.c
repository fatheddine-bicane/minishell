/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:48:51 by fbicane           #+#    #+#             */
/*   Updated: 2025/05/29 14:02:59 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

void	wait_child(pid_t pid, t_shell *shell)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		shell->exit_status = WEXITSTATUS(status);
	}
	if (WIFSIGNALED(status))
	{
		g_signal_flag = WTERMSIG(status);
		if (2 == g_signal_flag)
		{
			shell->exit_status = 130;
			g_signal_flag = 0;
			printf("\n");
		}
		if (3 == g_signal_flag)
		{
			shell->exit_status = 131;
			g_signal_flag = 0;
			printf("Quit: 3\n");
		}
	}

	printf("the exit status : %d\n", shell->exit_status);
}
