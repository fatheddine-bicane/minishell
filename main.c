/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 21:54:56 by fbicane           #+#    #+#             */
/*   Updated: 2025/04/06 21:54:58 by fbicane          ###   ########.fr       */
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
		if (!strncmp("cd", rl, 2))
		{
			ft_cd(NULL, envp);
		}
		else if (!strncmp("pwd", rl, 3))
			ft_pwd();
		printf("%s\n", rl);
	}
    return (0);
}
