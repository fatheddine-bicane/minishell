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


void	ft_exec_built_ins(char **command_arg, t_list **my_envp)
{
	if (0 == ft_strncmp(command_arg[0], "echo", 4))
	{
		ft_echo(command_arg, (*my_envp));
		/*exit(1);*/
		if (-1 == execve(NULL, NULL, NULL))
			printf("failed\n");
	}
	else if (0 == ft_strncmp(command_arg[0], "cd", 2))
	{
		ft_cd(command_arg[1]);
		exit(1);
	}
	else if (0 == ft_strncmp(command_arg[0], "pwd", 3))
	{
		ft_pwd();
		exit(1);
	}
	else if (0 == ft_strncmp(command_arg[0], "export", 6))
	{
		ft_export(NULL); // TODO: pass the original pointer
		exit(1);
	}
	else if (0 == ft_strncmp(command_arg[0], "unset", 5))
	{
		ft_unset(my_envp, command_arg); // TODO: check argument 0
		exit(1);
	}
	else if (0 == ft_strncmp(command_arg[0], "env", 3))
	{
		ft_env(*my_envp);
		exit(1);
	}
	else if (0 == ft_strncmp(command_arg[0], "exit", 4))
	{
		ft_exit();
		exit(1);
	}
	// TODO: free used memory (no execve to clean)
}
