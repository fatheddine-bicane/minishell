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
	if (!ft_strncmp("unset", rl, 5))
	{
		printf("test");
		/*char **arr = ft_unset(NULL, NULL);*/
		/*(void)arr;*/
		/*printf("%s------\n", rl + 6);*/
		return (1);
	}
	else if (!ft_strncmp("cd", rl, 2))
	{
		char **arr = ft_split(rl, ' ');
		if (!arr[1])
			ft_cd(NULL);
		else
			ft_cd(arr[1]);
		return (1);
	}
	else if (!ft_strncmp("pwd", rl, 3))
	{
		ft_pwd();
		return (1);
	}
	else if (!ft_strncmp("env", rl, 3))
	{
		ft_env((*my_envp));
		return (1);
	}
	else if (!ft_strncmp("echo", rl, 4))
	{
		ft_echo(rl);
		/*char **arr = ft_split(rl, ' ');*/
		/*if (!ft_strncmp(arr[1], "-n", 2))*/
		/*	ft_echo(true, arr);*/
		/*else*/
		/*	ft_echo(false, arr);*/
		return (1);
	}
	else if (!ft_strncmp("exit", rl, 4))
	{
		ft_exit();
		return (1);
	}
	else if (!ft_strncmp("export", rl, 6))
	{
		ft_export(NULL);
		return (1);
	}
	return (0);
}
