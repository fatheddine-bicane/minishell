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

int	ft_check_bultins(char *rl, t_list **my_envp)
{

	int	std_in_save = dup(STDIN_FILENO);
	if (-1 == std_in_save)
		return 0; // TODO: error mssg
	int	std_out_save = dup(STDOUT_FILENO);
	if (-1 == std_out_save)
		return 0; // TODO: error mssg




	if (!ft_strncmp("unset", rl, 5))
	{
		char **str = ft_split(rl, 32);
		ft_unset(my_envp, str);
		add_history(rl);
		dup2(std_in_save, STDIN_FILENO);
		dup2(std_out_save, STDOUT_FILENO);
		return (1);
	}
	else if (!ft_strncmp("cd", rl, 2))
	{
		char **arr = ft_split(rl, ' ');
		if (!arr[1])
			ft_cd(NULL, my_envp);
		else
			ft_cd(arr[1], my_envp);
		add_history(rl);
		return (1);
	}
	else if (!ft_strncmp("pwd", rl, 3))
	{
		ft_pwd();
		add_history(rl);
		dup2(std_in_save, STDIN_FILENO);
		dup2(std_out_save, STDOUT_FILENO);
		return (1);
	}
	else if (!ft_strncmp("env", rl, 3))
	{
		ft_env((*my_envp));
		add_history(rl);
		dup2(std_in_save, STDIN_FILENO);
		dup2(std_out_save, STDOUT_FILENO);
		return (1);
	}
	else if (!ft_strncmp("echo", rl, 4))
	{
		ft_echo(ft_split(rl, 32), *my_envp);
		add_history(rl);
		dup2(std_in_save, STDIN_FILENO);
		dup2(std_out_save, STDOUT_FILENO);
		return (1);
	}
	else if (!ft_strncmp("exit", rl, 4))
	{
		ft_exit();
		add_history(rl);
		return (1);
	}
	else if (!ft_strncmp("export", rl, 6))
	{
		ft_export(my_envp, ft_split(rl, 32));
		add_history(rl);
		dup2(std_in_save, STDIN_FILENO);
		dup2(std_out_save, STDOUT_FILENO);
		return (1);
	}
	return (0);
}
