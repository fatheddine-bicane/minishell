/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:36:30 by fbicane           #+#    #+#             */
/*   Updated: 2025/05/28 14:18:53 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

void	ft_exec_builtins(char **command_arg, t_list **my_envp, int *exit_stat)
{
	if (!ft_is_builtin(command_arg[0]))
	{
		ft_free_arr(command_arg);
		return ;
	}
	if (0 == ft_strncmp(command_arg[0], "echo", 4))
	{
		ft_echo(command_arg, (*my_envp), exit_stat);
		exit(*exit_stat);
	}
	else if (0 == ft_strncmp(command_arg[0], "cd", 2))
	{
		ft_cd(command_arg, my_envp, exit_stat);
		exit(*exit_stat);
	}
	else if (0 == ft_strncmp(command_arg[0], "pwd", 3))
	{
		ft_pwd(exit_stat);
		exit(*exit_stat);
	}
	else if (0 == ft_strncmp(command_arg[0], "export", 6))
	{
		ft_export(my_envp, command_arg, exit_stat);
		exit(*exit_stat);
	}
	else if (0 == ft_strncmp(command_arg[0], "unset", 5))
	{
		ft_unset(my_envp, command_arg); // TODO: check argument 0
		exit(*exit_stat);
	}
	else if (0 == ft_strncmp(command_arg[0], "env", 3))
	{
		ft_env(*my_envp, exit_stat);
		exit(*exit_stat);
	}
	else if (0 == ft_strncmp(command_arg[0], "exit", 4))
	{
		ft_exit(exit_stat);
		exit(*exit_stat);
	}
	// TODO: free used memory (no execve to clean)
}
