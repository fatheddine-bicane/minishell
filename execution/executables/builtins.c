/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 21:37:37 by fbicane           #+#    #+#             */
/*   Updated: 2025/04/19 16:58:49 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

/*int	ft_check_bultins(char *rl, t_list **my_envp)*/
int	run_bultins(char **argv, t_list **my_envp, int *exit_stat)
{
	bool	is_builtin = false;

	int	std_in_save = dup(STDIN_FILENO);
	if (-1 == std_in_save)
		return 0; // TODO: error mssg
	int	std_out_save = dup(STDOUT_FILENO);
	if (-1 == std_out_save)
		return 0; // TODO: error mssg



	/*add_history(argv);*/
	if (!ft_strncmp("unset", argv[0], 5))
	{
		/*char **str = ft_split(rl, 32);*/
		ft_unset(my_envp, argv);
		is_builtin = true;
	}
	else if (!ft_strncmp("cd", argv[0], 2))
	{
		ft_cd(argv, my_envp, exit_stat);
		/*char **arr = ft_split(rl, ' ');*/
		/*if (!arr[1])*/
		/*	ft_cd(NULL, my_envp, exit_stat);*/
		/*else*/
		/*	ft_cd(arr[1], my_envp, exit_stat);*/
		is_builtin = true;
	}
	else if (!ft_strncmp("pwd", argv[0], 3))
	{
		ft_pwd(exit_stat);
		is_builtin = true;
	}
	else if (!ft_strncmp("env", argv[0], 3))
	{
		ft_env((*my_envp), exit_stat);
		is_builtin = true;
	}
	else if (!ft_strncmp("echo", argv[0], 4))
	{
		ft_echo(argv, *my_envp, exit_stat);
		is_builtin = true;
	}
	else if (!ft_strncmp("exit", argv[0], 4))
	{
		ft_exit(exit_stat, argv, my_envp);
		is_builtin = true;
	}
	else if (!ft_strncmp("export", argv[0], 6))
	{
		ft_export(my_envp, argv, exit_stat);
		is_builtin = true;
	}

	dup2(std_in_save, STDIN_FILENO);
	dup2(std_out_save, STDOUT_FILENO);
	ft_free_arr(argv);
	if (is_builtin)
		return (1);
	return (0);
}
