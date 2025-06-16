/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:08:26 by fbicane           #+#    #+#             */
/*   Updated: 2025/05/31 17:46:59 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

void	exit_error(t_shell *shell, int error_mssg)
{
	int	exit_status;

	if (1 == error_mssg)
		return (ast_free(shell->root_to_free),
			free_my_envp(&shell->my_envp), exit(shell->exit_status));
	else if (2 == error_mssg)
	{
		ft_printf("exit\n");
		exit_status = ft_atoi(shell->cmd->u_as.exec.argv[1]) % 256;
		return (ast_free(shell->root_to_free),
			free_my_envp(&shell->my_envp), exit(exit_status));
	}
	else if (3 == error_mssg)
	{
		ft_printf(RED"exit: numeric argument required\n"RESET);
		return (ast_free(shell->root_to_free),
			free_my_envp(&shell->my_envp), exit(255));
	}
	else if (4 == error_mssg)
	{
		ft_printf(RED"exit: numeric argument required\n"RESET);
		return (ast_free(shell->root_to_free),
			free_my_envp(&shell->my_envp), exit(255));
	}
}
