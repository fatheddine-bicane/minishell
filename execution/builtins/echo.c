/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 15:34:38 by fbicane           #+#    #+#             */
/*   Updated: 2025/06/12 15:24:54 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

static bool	handl_new_line_utils(char **argv, int *i)
{
	int	j;

	if (!argv[*i])
		return (true);
	j = 0;
	if ('-' != argv[1][j++])
		return (true);
	while ('n' == argv[1][j])
		j++;
	if (argv[1][j])
		return (true);
	(*i)++;
	return (false);
}

static bool	handle_new_line(char **argv, int *i)
{
	bool	print_new_line;
	int		j;

	print_new_line = handl_new_line_utils(argv, i);
	if (false == print_new_line)
	{
		while (argv[*i])
		{
			j = 0;
			if ('-' != argv[*i][0])
				break ;
			j++;
			while ('n' == argv[*i][j])
				j++;
			if (argv[*i][j])
				break ;
			(*i)++;
		}
	}
	return (print_new_line);
}

void	ft_echo(t_shell *shell)
{
	int		i;
	bool	new_line;

	i = 1;
	new_line = handle_new_line(shell->cmd->u_as.exec.argv, &i);
	while (shell->cmd->u_as.exec.argv[i])
	{
		printf("%s", shell->cmd->u_as.exec.argv[i]);
		if (shell->cmd->u_as.exec.argv[i + 1])
			printf(" ");
		i++;
	}
	if (new_line)
		printf("\n");
	shell->exit_status = 0;
}
