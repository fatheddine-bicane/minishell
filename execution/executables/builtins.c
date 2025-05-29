/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 21:37:37 by fbicane           #+#    #+#             */
/*   Updated: 2025/05/29 16:20:47 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

// INFO: to call before handling redirections mainly if executing a builtin
void	save_std_files(bool save)
{
	static int	std_in_save;
	static int	std_out_save;

	if (true == save)
	{
		std_in_save = dup(STDIN_FILENO);
		if (-1 == std_in_save)
			return ; // TODO: error mssg
		int	std_out_save = dup(STDOUT_FILENO);
		if (-1 == std_out_save)
			return ; // TODO: error mssg
	}
	else
	{
		dup2(std_in_save, STDIN_FILENO);
		dup2(std_out_save, STDOUT_FILENO);
	}
}

void	run_bultins(char **argv, t_list **my_envp, int *exit_stat)
{
	if (!ft_strncmp("unset", argv[0], 5))
	{
		ft_unset(my_envp, argv);
	}
	else if (!ft_strncmp("cd", argv[0], 2))
	{
		ft_cd(argv, my_envp, exit_stat);
	}
	else if (!ft_strncmp("pwd", argv[0], 3))
	{
		ft_pwd(exit_stat);
	}
	else if (!ft_strncmp("env", argv[0], 3))
	{
		ft_env((*my_envp), exit_stat);
	}
	else if (!ft_strncmp("echo", argv[0], 4))
	{
		ft_echo(argv, *my_envp, exit_stat);
	}
	else if (!ft_strncmp("exit", argv[0], 4))
	{
		ft_exit(exit_stat, argv, my_envp);
	}
	else if (!ft_strncmp("export", argv[0], 6))
	{
		ft_export(my_envp, argv, exit_stat);
	}
	/*ft_free_arr(argv);*/
}
