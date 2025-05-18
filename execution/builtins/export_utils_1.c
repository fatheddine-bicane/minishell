/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 15:32:59 by fbicane           #+#    #+#             */
/*   Updated: 2025/05/17 15:37:21 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

void	ft_sort_myenvp(t_list *my_envp)
{
	char	**envp_sort;
	char	*tmp;
	int		i;

	envp_sort = ft_prep_envp(my_envp);
	i = 0;
	while(envp_sort[i])
	{
		int (j) = i + 1;
		while (envp_sort[j])
		{
			if (0 < ft_strncmp(envp_sort[i], envp_sort[j], ft_strlen(envp_sort[i])))
			{
				tmp = envp_sort[i];
				envp_sort[i] = envp_sort[j];
				envp_sort[j] = tmp;
			}
			j++;
		}
		i++;
	}
	i = -1;
	while (envp_sort[++i])
		printf("%s\n", envp_sort[i]);
	ft_free_arr(envp_sort);
}

bool	ft_to_append(char *variable)
{
	int	i;

	i = 0;
	while ('=' != variable[i] && variable[i])
		i++;
	if ('+' == variable[i - 1])
		return (true);
	return (false);
}

char	*ft_append_equal(char *variable)
{
	int		i;

	i = 0;
	while ('=' != variable[i] && variable)
		i++;
	if ('=' != variable[i])
	{
		free(variable);
		return(ft_strjoin(variable, "="));
	}
	return (variable);
	// INFO: variable dosent add '=' when the variable exported befor dosent have the = sign
}

void	ft_append_to_varriable(t_list **my_envp, char *variable)
{
	t_list	*tmp;
	int		i;

	i = 0;
	while (variable[i] && '+' != variable[i])
		i++;
	tmp = *my_envp;
	while (tmp)
	{
		if (!ft_strncmp(tmp->content, variable, i))
		{
			tmp->content = ft_append_equal(tmp->content);
			char (*varr_result) = ft_strjoin(tmp->content, variable + i + 2);
			free(tmp->content);
			tmp->content = varr_result;
			return ;
		}
		tmp = tmp->next;
	}
}

void	ft_add_variable(t_list **my_envp, char *variable)
{
	int	i;

	i = 0;
	bool (found_plus) = false;
	char (res[ft_strlen(variable) - 1]);
	while (variable[i])
	{
		if ('+' == variable[i] && !found_plus)
		{
			found_plus = true;
			i++;
			continue ;
		}
		res[i] = variable[i];
		i++;
	}
	res[i] = '\0';
	ft_lstadd_back(my_envp, ft_lstnew(ft_strdup(res)));
}
