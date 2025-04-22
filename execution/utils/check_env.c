/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 20:25:53 by fbicane           #+#    #+#             */
/*   Updated: 2025/04/18 21:41:21 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

bool	ft_envpcmp(char *variable, char *envp_l)
{
	int (i) = 0;
	while (envp_l[i] != '=')
		i++;
	char (str[i]);
	i = 0;
	while (envp_l[i] != '=')
		str[i] = envp_l[i];
	str[i] = '\0';
	if (!ft_strncmp(variable, str, ft_strlen(variable)))
		return (true);
	else
		return (false);
}

bool	ft_variable_exist(t_list *my_envp, char *variable)
{
	while (my_envp)
	{
		if (ft_envpcmp(variable, my_envp->content))
			return (true);
		my_envp = my_envp->next;
	}
	return (false);
}

static char	*ft_find_var(char *variable, t_list *my_vars)
{
	int	i;

	while (my_vars)
	{
		i = 0;
		while (variable[i] != '=' && variable[i])
			i++;
		char	str[i];
		i = 0;
		while (variable[i] != '=' && variable[i])
		{
			str[i] = variable[i];
			i++;
		}
		str[i] = '\0';
		if (!ft_strncmp(variable, str, ft_strlen(variable)))
		{
			return ((char *)my_vars->content);
		}
		my_vars = my_vars->next;
	}
	return (NULL);
}

void	ft_export_util(t_list **my_envp, char *variable, t_list *my_vars)
{
	if (!ft_variable_exist((*my_envp), variable))
	{
		char (*var_to_export) = ft_find_var(variable, my_vars);
		if (!var_to_export)
		{
			return ;
		}
		ft_lstadd_back(my_envp, ft_lstnew(var_to_export));
	}
}
