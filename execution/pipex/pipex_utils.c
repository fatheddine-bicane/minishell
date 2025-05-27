/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:36:30 by fbicane           #+#    #+#             */
/*   Updated: 2025/04/30 12:32:38 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

bool	ft_is_builtin(char *command)
{
	if (0 == ft_strncmp(command, "echo", 4))
		return (true);
	else if (0 == ft_strncmp(command, "cd", 2))
		return (true);
	else if (0 == ft_strncmp(command, "pwd", 3))
		return (true);
	else if (0 == ft_strncmp(command, "export", 6))
		return (true);
	else if (0 == ft_strncmp(command, "unset", 5))
		return (true);
	else if (0 == ft_strncmp(command, "env", 3))
		return (true);
	else if (0 == ft_strncmp(command, "exit", 4))
		return (true);
	else
		return (false);
}


void	ft_exec_builtins(char **command_arg, t_list **my_envp, int *exit_stat)
{
	int	b;
	if (!ft_is_builtin(command_arg[0]))
	{
		ft_free_arr(command_arg);
		return ;
	}
	if (0 == ft_strncmp(command_arg[0], "echo", 4))
	{
		ft_echo(command_arg, (*my_envp), exit_stat);
		exit(0);
	}
	else if (0 == ft_strncmp(command_arg[0], "cd", 2))
	{
		ft_cd(command_arg[1], my_envp);
		exit(0);
	}
	else if (0 == ft_strncmp(command_arg[0], "pwd", 3))
	{
		ft_pwd();
		exit(0);
	}
	else if (0 == ft_strncmp(command_arg[0], "export", 6))
	{
		ft_export(my_envp, command_arg);
		exit(0);
	}
	else if (0 == ft_strncmp(command_arg[0], "unset", 5))
	{
		ft_unset(my_envp, command_arg); // TODO: check argument 0
		exit(0);
	}
	else if (0 == ft_strncmp(command_arg[0], "env", 3))
	{
		ft_env(*my_envp);
		exit(0);
	}
	else if (0 == ft_strncmp(command_arg[0], "exit", 4))
	{
		ft_exit();
		exit(0);
	}
	// TODO: free used memory (no execve to clean)
}
