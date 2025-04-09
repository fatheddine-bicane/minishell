/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 21:54:56 by fbicane           #+#    #+#             */
/*   Updated: 2025/04/09 15:55:18 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	while (1)
	{
		char *rl = NULL;
		rl = readline("shell_dyal_dri > ");
		if (!ft_strncmp("test", rl, 4))
			perror(strerror(-1));
		if (!ft_strncmp("cd", rl, 2))
		{
			char **arr = ft_split(rl, ' ');
			if (!arr[1])
				ft_cd(NULL);
			else
				ft_cd(arr[1]);
		}
		else if (!ft_strncmp("pwd", rl, 3))
		{
			ft_pwd();
		}
		else if (!ft_strncmp("env", rl, 3))
		{
			ft_env(envp);
		}
		else if (!ft_strncmp("echo", rl, 4))
		{
			char **arr = ft_split(rl, ' ');
			if (!ft_strncmp(arr[1], "-n", 2))
				ft_echo(true, arr);
			else
				ft_echo(false, arr);
		}
		else if (!ft_strncmp("exit", rl, 4))
		{
			ft_exit();
		}
		else if (!ft_strncmp("export", rl, 6))
		{
			ft_export(envp);
		}
		if (errno != 0)
			perror(strerror(errno));
		add_history(rl);
	}
    return (0);
}
