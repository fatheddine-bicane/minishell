/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 21:54:56 by fbicane           #+#    #+#             */
/*   Updated: 2025/04/12 16:17:12 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

int main(int argc, char **argv, char **envp)
{
	/*t_list *my_envp;*/
	t_array *my_envp;

	(void)argc;
	(void)argv;
	while (1)
	{
		my_envp = ft_set_env_(envp);
		char *rl = NULL;
		rl = readline("====> ");
		if (!ft_strncmp("unset", rl, 5))
		{
			ft_unset(&my_envp, NULL);
			/*printf("%s------\n", rl + 6);*/
		}
		else if (!ft_strncmp("test", rl, 4))
			perror(strerror(-1));
		else if (!ft_strncmp("cd", rl, 2))
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
			ft_env(my_envp);
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
	write(1, "no seg here\n", 12);
    return (0);
}
