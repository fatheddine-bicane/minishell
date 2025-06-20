/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:48:51 by fbicane           #+#    #+#             */
/*   Updated: 2025/06/17 00:45:48 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

void	wait_child(pid_t pid, t_shell *shell)
{
	int	status;
	int	tmp;

	tmp = 0;
	status = 0;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		tmp = WTERMSIG(status);
		if (2 == tmp)
		{
			shell->exit_status = 130;
			printf("\n");
		}
		if (3 == tmp)
		{
			shell->exit_status = 131;
			write(STDOUT_FILENO, "Quit: 3\n", 9);
		}
	}
}
