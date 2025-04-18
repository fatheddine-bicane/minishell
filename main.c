/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 21:54:56 by fbicane           #+#    #+#             */
/*   Updated: 2025/04/18 21:40:53 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

int main(int argc, char **argv, char **envp)
{
	t_list *my_envp;

	(void)argc;
	(void)argv;

	my_envp = ft_set_env(envp);
	while (1)
	{
		char *rl = NULL;
		rl = readline("====> ");
		ft_check_bultins(rl, &my_envp);
		if (errno != 0)
			perror(strerror(errno));
		add_history(rl);
	}
	write(1, "no seg here\n", 12);
    return (0);
}
