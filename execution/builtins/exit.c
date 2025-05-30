/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:29:01 by fbicane           #+#    #+#             */
/*   Updated: 2025/05/28 18:47:22 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

bool	argument_is_numeric(char *argument)
{
	int	i;

	i = 0;
	while (argument[i])
	{
		if (!ft_isdigit(argument[i]))
			return (false);
		i++;
	}
	return (true);
}

void	ft_exit(int *exit_stat, char **argv, t_list **my_envp)
{
	// TODO: free cmg the ast
	(void)my_envp;
	if (!argv[1])
	{
		ft_free_arr(argv);
		free_my_envp(my_envp);
		exit(0);
		(*exit_stat) = 0;
	}
	else if (argv[1] && !argv[2])
	{
		if (argument_is_numeric(argv[1]))
		{
			printf("exit\n");
			ft_free_arr(argv); // TODO: free ast
			free_my_envp(my_envp);
			exit(ft_atoi(argv[1]));
		}
		else
		{
			ft_putstr_fd("exit: numeric argument required\n", 2);
			exit(255);
		}
	}
	else
	{
		if (!argument_is_numeric(argv[1]))
		{
			ft_putstr_fd("exit: numeric argument required\n", 2);
			exit(255);
		}
		printf("exit\n");
		ft_putstr_fd("exit: too many arguments\n", 2);
		(*exit_stat) = 1;
	}

}
