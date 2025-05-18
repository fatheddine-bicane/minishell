/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 15:38:03 by fbicane           #+#    #+#             */
/*   Updated: 2025/05/17 15:47:25 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

void	ft_update_var(t_list **my_envp, char *variable)
{
	t_list	*tmp_ptr;
	int		i;

	i = 0;
	while (variable[i] && '=' != variable[i])
		i++;

	tmp_ptr = *my_envp;
	while (tmp_ptr)
	{
		if (!ft_strncmp(tmp_ptr->content, variable, i))
		{
			free(tmp_ptr->content);
			tmp_ptr->content = ft_strdup(variable);
			return ;
		}
		tmp_ptr = tmp_ptr->next;
	}
}

static bool	ft_equal_in_var(char *variable)
{
	int	i;

	i = 0;
	while ('=' != variable[i] && variable[i])
		i++;
	if ('=' == variable[i])
		return (true);
	return (false);
}

void	ft_export_utils_1(t_list **my_envp, char *variable)
{
	if (ft_equal_in_var(variable))
	{
		if (ft_to_append(variable))
			ft_append_to_varriable(my_envp, variable);
		else
			ft_update_var(my_envp, variable);
	}
}
