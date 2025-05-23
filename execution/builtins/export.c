/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:27:43 by fbicane           #+#    #+#             */
/*   Updated: 2025/05/09 19:41:07 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

bool	ft_variable_exist(t_list *my_envp, char *varaible)
{
	int		i;

	i = 0;
	while (varaible[i] && '=' != varaible[i])
		i++;

	while (my_envp)
	{
		if (!ft_strncmp(my_envp->content, varaible, i))
			return (true);
		my_envp = my_envp->next;
	}
	return (false);
}

void	ft_var_exist(t_list **my_envp, char *variable)
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
				ft_var_exist(my_envp, variables[vars_i]);
			}
			else
				ft_lstadd_back(my_envp, ft_lstnew(variables[vars_i]));
			vars_i++;
		}
	}
}
