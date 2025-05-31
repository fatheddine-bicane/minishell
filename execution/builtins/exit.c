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

/*void	ft_exit(t_shell *shell)*/
void	ft_exit(t_shell *shell)
{
	// TODO: free cmg the ast
	if (!shell->cmd->u_as.exec.argv[1])
	{
		/*free_my_envp();*/
		ast_free(shell->cmd);
		free_my_envp(&shell->my_envp);
		exit(0);
	}
	else if (shell->cmd->u_as.exec.argv[1] && !shell->cmd->u_as.exec.argv[2])
	{
		if (argument_is_numeric(shell->cmd->u_as.exec.argv[1]))
		{
			printf("exit\n");
			/*free_my_envp(my_envp);*/
			ast_free(shell->cmd);
			free_my_envp(&shell->my_envp);
			exit(ft_atoi(shell->cmd->u_as.exec.argv[1]));
		}
		else
		{
			ft_putstr_fd("exit: numeric argument required\n", 2);
			ast_free(shell->cmd);
			free_my_envp(&shell->my_envp);
			exit(255);
		}
	}
	else
	{
		if (!argument_is_numeric(shell->cmd->u_as.exec.argv[1]))
		{
			ft_putstr_fd("exit: numeric argument required\n", 2);
			ast_free(shell->cmd);
			exit(255);
		}
		printf("exit\n");
		ft_putstr_fd("exit: too many arguments\n", 2);
		shell->exit_status = 1;
	}

}
