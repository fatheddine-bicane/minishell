/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:29:01 by fbicane           #+#    #+#             */
/*   Updated: 2025/05/31 17:50:16 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

// INFO: check if argument is numerical
static bool	argument_is_numeric(char *argument)
{
	int	i;

	i = 0;
	if ('+' == argument[i])
		i++;
	while (argument[i])
	{
		if (0 == ft_isdigit(argument[i]))
			return (false);
		i++;
	}
	return (true);
}

static bool	argument_is_negative(char *argument)
{
	int	i;

	i = 0;
	if ('-' == argument[i])
		i++;
	while (argument[i])
	{
		if (0 == ft_isdigit(argument[i]))
			return (false);
		i++;
	}
	return (true);
}

void	ft_exit_one_arguemt(t_shell *shell)
{
	int	exit_negative;

	// INFO: if the argument is numerical
	if (argument_is_numeric(shell->cmd->u_as.exec.argv[1]))
		exit_error(shell, 2);
		// INFO: the argument is negative
	else if (argument_is_negative(shell->cmd->u_as.exec.argv[1]))
	{
	exit_negative = ft_atoi(shell->cmd->u_as.exec.argv[1]) % 256;
	ast_free(shell->root_to_free);
	free_my_envp(&shell->my_envp);
	exit(exit_negative);
}
	// INFO: the argument is not numerical
	else
	exit_error(shell, 3);
}

void	ft_exit(t_shell *shell)
{
	// INFO: exit with no arguments
	if (!shell->cmd->u_as.exec.argv[1])
		exit_error(shell, 1);
	// INFO: exit and one argument
	else if (shell->cmd->u_as.exec.argv[1] && !shell->cmd->u_as.exec.argv[2])
		ft_exit_one_arguemt(shell);
	// INFO: exit with n arguments
	else
	{
		// INFO: if the first agument is negative
		if (true == argument_is_negative(shell->cmd->u_as.exec.argv[1]))
		{
			ft_printf(RED"exit\nexit: too many arguments\n"RESET);
			shell->exit_status = 1;
			return ;
		}
		// INFO: if the first agument is not numerical
		if (false == argument_is_numeric(shell->cmd->u_as.exec.argv[1]))
			exit_error(shell, 4);
		ft_printf(RED"exit\nexit: too many arguments\n"RESET);
		shell->exit_status = 1;
	}
}
