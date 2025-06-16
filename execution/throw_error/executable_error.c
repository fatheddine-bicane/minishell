/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 11:35:10 by fbicane           #+#    #+#             */
/*   Updated: 2025/06/05 13:20:13 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

void	executable_error(t_shell *shell,
		int error_mssg, char **prep_envp)
{
	if (1 == error_mssg)
	{
		ft_printf(RED"failed to execute command\n"RESET);
		ft_free_arr(prep_envp);
		free_my_envp(&shell->my_envp);
		ast_free(shell->root_to_free);
		ft_free_arr(shell->heredocs_files);
		exit(127);
	}
	else if (2 == error_mssg)
	{
		ft_free_arr(prep_envp);
		free_my_envp(&shell->my_envp);
		ft_free_arr(shell->heredocs_files);
		shell->exit_status = 127;
		return ;
	}
	else if (3 == error_mssg)
	{
		ast_free(shell->root_to_free);
		free_my_envp(&shell->my_envp);
		ft_free_arr(shell->heredocs_files);
		exit(127);
	}
}

void	executable_error_2(t_shell *shell, int error_mssg)
{
	if (4 == error_mssg)
	{
		ft_free_arr(shell->heredocs_files);
		shell->exit_status = 127;
		return ;
	}
	else if (5 == error_mssg)
	{
		shell->exit_status = 127;
		ft_printf(RED"%s:  No such file or director\n"RESET,
			shell->cmd->u_as.exec.argv[0]);
		return ;
	}
	else if (6 == error_mssg)
	{
		ft_free_arr(shell->heredocs_files);
		shell->exit_status = 127;
		ft_printf(RED"%s:  No such file or director\n"RESET,
			shell->cmd->u_as.exec.argv[0]);
		return ;
	}
}

void	executable_error_3(t_shell *shell, t_executable *exec,
		int error_mssg, pid_t pid)
{
	if (7 == error_mssg)
	{
		ft_printf(RED"failed to execute command\n"RESET);
		ft_free_arr(exec->penvp);
		ft_free_arr(exec->paths);
		free_my_envp(&shell->my_envp);
		ast_free(shell->root_to_free);
		ft_free_arr(shell->heredocs_files);
		exit(127);
	}
	else if (8 == error_mssg)
	{
		ft_free_arr(exec->penvp);
		ft_free_arr(exec->paths);
		free_my_envp(&shell->my_envp);
		shell->exit_status = 127;
		return (ft_free_arr(shell->heredocs_files));
	}
	else if (9 == error_mssg)
	{
		ft_free_arr(exec->penvp);
		wait_child(pid, shell);
		return (ft_free_arr(exec->paths));
	}
}

void	executable_error_4(t_shell *shell, t_executable *exec,
		int error_mssg, pid_t pid)
{
	if (10 == error_mssg)
	{
		ft_free_arr(exec->penvp);
		wait_child(pid, shell);
		ft_free_arr(exec->paths);
		return ;
	}
	else if (11 == error_mssg)
	{
		ft_free_arr(exec->penvp);
		return (ft_free_arr(exec->paths));
	}
	else if (12 == error_mssg)
	{
		ast_free(shell->root_to_free);
		free_my_envp(&shell->my_envp);
		return (ft_free_arr(shell->heredocs_files), exit(127));
	}
	else if (13 == error_mssg)
	{
		shell->exit_status = 127;
		return (ft_free_arr(shell->heredocs_files));
	}
}

void	executable_error_5(t_shell *shell, int error_mssg)
{
	if (14 == error_mssg)
	{
		shell->exit_status = 127;
		ft_printf(RED"%s: failed to execute command\n"RESET,
			shell->cmd->u_as.exec.argv[0]);
		return ;
	}
	else if (15 == error_mssg)
	{
		ft_free_arr(shell->heredocs_files);
		shell->exit_status = 127;
		ft_printf(RED"%s: failed to execute command\n"RESET,
			shell->cmd->u_as.exec.argv[0]);
		return ;
	}
}
