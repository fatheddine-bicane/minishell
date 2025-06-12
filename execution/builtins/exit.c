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

void	ft_exit(t_shell *shell)
{
	int	exit_negative;

	if (!shell->cmd->u_as.exec.argv[1]) // INFO: exit with no arguments
		exit_error(shell, 1);
	else if (shell->cmd->u_as.exec.argv[1] && !shell->cmd->u_as.exec.argv[2]) // INFO: exit and one argument 
	{
		if (argument_is_numeric(shell->cmd->u_as.exec.argv[1])) // INFO: if the argument is numerical
			exit_error(shell, 2);
		else if (argument_is_negative(shell->cmd->u_as.exec.argv[1])) // INFO: the argument is negative
		{
			exit_negative = ft_atoi(shell->cmd->u_as.exec.argv[1]) % 256;
			ast_free(shell->root_to_free);
			free_my_envp(&shell->my_envp);
			exit(exit_negative);
		}
		else // INFO: the argument is not numerical
			exit_error(shell, 3);
	}
	else // INFO: exit with n arguments
	{
		if (true == argument_is_negative(shell->cmd->u_as.exec.argv[1])) // INFO: if the first agument is negative
		{
			ft_putstr_fd("exit\n", 2);
			ft_putstr_fd("exit: too many arguments\n", 2);
			shell->exit_status = 1;
		}
		if (false == argument_is_numeric(shell->cmd->u_as.exec.argv[1])) // INFO: if the first agument is not numerical
			exit_error(shell, 4);
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("exit: too many arguments\n", 2);
		shell->exit_status = 1;
	}

}
