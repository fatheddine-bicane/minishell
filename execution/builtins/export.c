/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:27:43 by fbicane           #+#    #+#             */
/*   Updated: 2025/05/31 18:59:55 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

static bool	ft_variable_exist(t_shell *shell, char *varaible)
{
	int		i;
	t_list	*tmp;

	i = 0;
	while (varaible[i] && '=' != varaible[i])
		i++;

	if ('+' == varaible[i - 1])
		i--;
	tmp = shell->my_envp;
	while (tmp)
	{
		if (!ft_strncmp(tmp->content, varaible, i))
			return (true);
		tmp = tmp->next;
	}
	return (false);
}


static bool	ft_valid_argument(char *variable)
{
	int	i;

	i = 0;
	if (!ft_isalpha(variable[i]) && '_' != variable[i])
		return (false);
	while ('=' != variable[i] && variable[i])
	{
		if ('+' == variable[i] && '=' != variable[i + 1])
			return (false);
		if ('+' == variable[i] && '=' == variable[i + 1])
			break ;
		if (!ft_isalpha(variable[i]) && !ft_isdigit(variable[i]))
			return (false);
		i++;
	}
	return (true);
}

void	ft_export(t_shell *shell)
{
	if (!shell->cmd->u_as.exec.argv[1]) // INFO: export with no argumets
		ft_sort_myenvp(shell);
	else
	{
		int (vars_i) = 1;
		while (shell->cmd->u_as.exec.argv[vars_i])
		{
			if (!ft_valid_argument(shell->cmd->u_as.exec.argv[vars_i])) // INFO: checking if var name is valid syntax
			{
				vars_i++;
				ft_putstr_fd("not valid argument", 2);
				continue;
				// TODO: error mssg
			}
			if (ft_variable_exist(shell, shell->cmd->u_as.exec.argv[vars_i])) // INFO: checking if var name exist in my_envp
				ft_export_utils_1(shell, shell->cmd->u_as.exec.argv[vars_i]);
			else
			{
				if (ft_to_append(shell->cmd->u_as.exec.argv[vars_i])) // INFO: checking if var need to append (name+=value_to_add)
					ft_add_variable(shell, shell->cmd->u_as.exec.argv[vars_i]);
				else
					ft_lstadd_back(&shell->my_envp, ft_lstnew(ft_strdup(shell->cmd->u_as.exec.argv[vars_i])));
			}
			vars_i++;
		}
	}
	shell->exit_status = 0;
}
