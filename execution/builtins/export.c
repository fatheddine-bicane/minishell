/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:27:43 by fbicane           #+#    #+#             */
/*   Updated: 2025/05/16 16:05:32 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

bool	ft_variable_exist(t_list *my_envp, char *varaible)
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

bool	ft_variable_append(char *variable)
{
	int	i;

	i = 0;
	while ('=' != variable[i] && variable[i])
		i++;
	if ('+' == variable[i - 1])
		return (true);
	return (false);
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

void	ft_export(t_list **my_envp, char **variables)
{
	int		vars_i; // INFO: variables_index

	if (!variables[1])
	{
		ft_sort_myenvp(*my_envp);
		/*ft_env(*my_envp);*/
		// TODO: print envp in alphabetical order 
	}
	else
	{
		vars_i = 1;
		while (variables[vars_i])
		{
			if (ft_variable_exist(*my_envp, variables[vars_i]))
			{
				if (ft_variable_append(variables[vars_i]))
				{
					ft_append_to_varriable(my_envp, variables[vars_i]);
				}
				else
				{
					ft_update_var(my_envp, variables[vars_i]);
				}
			}
			else
			{
				if (ft_variable_append(variables[vars_i]))
				{
					ft_add_variable(my_envp, variables[vars_i]);
				}
				else
					ft_lstadd_back(my_envp, ft_lstnew(variables[vars_i]));
			}
			vars_i++;
		}
	}
}
