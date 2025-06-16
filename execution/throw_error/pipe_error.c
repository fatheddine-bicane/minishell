/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 20:32:52 by fbicane           #+#    #+#             */
/*   Updated: 2025/06/01 21:20:14 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

void	pipe_error(t_shell *shell, int error_mssg, char **prep_envp)
{
	if (1 == error_mssg)
	{
		ft_free_arr(prep_envp);
		shell->exit_status = 127;
	}
	else if (2 == error_mssg)
	{
		free_my_envp(&shell->my_envp);
		shell->exit_status = 127;
	}
	else if (3 == error_mssg)
	{
		shell->exit_status = 127;
		perror(shell->cmd->u_as.exec.argv[0]);
	}
}

void	pipe_error_2(t_shell *shell, int error_mssg, t_executable *executable)
{
	if (4 == error_mssg)
	{
		free_my_envp(&shell->my_envp);
		shell->exit_status = 127;
	}
	else if (5 == error_mssg)
	{
		ft_free_arr(executable->paths);
		ft_putstr_fd(shell->cmd->u_as.exec.argv[0], 2);
		ft_putstr_fd(":  No such file or director\n", 2);
		shell->exit_status = 127;
	}
	else if (6 == error_mssg)
	{
		free(executable->path);
		ft_free_arr(executable->paths);
		free_my_envp(&shell->my_envp);
		shell->exit_status = 127;
	}
}

void	pipe_error_3(t_shell *shell, t_executable *executable,
		int error_mssg, pid_t pid)
{
	(void)executable;
	(void)pid;
	if (7 == error_mssg)
	{
		free_my_envp(&shell->my_envp);
		shell->exit_status = 127;
	}
	else if (8 == error_mssg)
	{
		shell->exit_status = 127;
		ft_putstr_fd(shell->cmd->u_as.exec.argv[0], 2);
		ft_putstr_fd(":  No such file or director\n", 2);
	}
}
