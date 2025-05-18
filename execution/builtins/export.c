/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:27:43 by fbicane           #+#    #+#             */
/*   Updated: 2025/05/17 15:49:02 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

static bool	ft_variable_exist(t_list *my_envp, char *varaible)
{
	int		i;

	i = 0;
	while (varaible[i] && '=' != varaible[i])
		i++;

	if ('+' == varaible[i - 1])
		i--;
	while (my_envp)
	{
		if (!ft_strncmp(my_envp->content, varaible, i))
			return (true);
		my_envp = my_envp->next;
	}
	return (false);
}


static bool	ft_valid_argument(char *variable)
{
	int	i;

	i = 0;
	if (!ft_isalpha(variable[i]) || '_' != variable[i])
		return (false);
	while ('=' != variable[i] && variable[i])
	{
		if ('+' == variable[i] && '=' != variable[i + 1])
			return (false);
		if (!ft_isalpha(variable[i]) || !ft_isdigit(variable[i]))
			return (false);
		i++;
	}
	return (true);
}



void	ft_export(t_list **my_envp, char **variables)
{
	if (!variables[1])
		ft_sort_myenvp(*my_envp);
	else
	{
		int (vars_i) = 1;
		while (variables[vars_i])
		{
			if (!ft_valid_argument(variables[vars_i]) == false)
			{
				vars_i++;
				continue;
				// TODO: error mssg
			}
			if (ft_variable_exist(*my_envp, variables[vars_i]))
				ft_export_utils_1(my_envp, variables[vars_i]);
			else
			{
				if (ft_to_append(variables[vars_i]))
					ft_add_variable(my_envp, variables[vars_i]);
				else
					ft_lstadd_back(my_envp, ft_lstnew(variables[vars_i]));
			}
			vars_i++;
		}
	}
	ft_free_arr(variables);
}
