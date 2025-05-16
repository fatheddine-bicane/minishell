/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:55:55 by fbicane           #+#    #+#             */
/*   Updated: 2025/05/16 14:17:15 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

static bool	ft_first_node(t_unset *unset, t_list **my_envp, char **variables)
{
	// INFO: check first node
	unset->env_cont = (char *)(*my_envp)->content;
	unset->i = 0;
	while (unset->env_cont[unset->i] && unset->env_cont[unset->i] != '=')
		unset->i++;

	if (!ft_strncmp(unset->env_cont, variables[unset->v_i], unset->i))
	{
		unset->env_to_del = (*my_envp);
		(*my_envp) = (*my_envp)->next;
		(void)unset->env_to_del;
		// TODO: free env_to_del content
		free(unset->env_to_del);
		return (true);
	}
	return (false);
}

static int	ft_rest_nodes(t_unset *unset, t_list **my_envp, char **variables)
{
	// INFO: check the rest nodes
	unset->tmp_envp = (*my_envp);
	while (unset->tmp_envp)
	{
		if (NULL == unset->tmp_envp->next)
			return (0);
		unset->env_cont = (char *)unset->tmp_envp->next->content;
		unset->i = 0;
		while (unset->env_cont[unset->i] && unset->env_cont[unset->i] != '=')
			unset->i++;
		if (!ft_strncmp(unset->env_cont, variables[unset->v_i], unset->i))
		{
			unset->env_to_del = unset->tmp_envp->next;
			unset->tmp_envp->next = unset->tmp_envp->next->next;
			(void)unset->env_to_del;
			// TODO: free env_to_del content
			free(unset->env_to_del);
			unset->skip_loop = true;
			break ;
		}
		unset->tmp_envp = unset->tmp_envp->next;
	}
	return (2);
}

void	ft_unset(t_list **my_envp, char **variables)
{
	t_unset	unset;
	int		check;

	if (NULL == variables)
		return;

	unset.v_i = 1;
	unset.skip_loop = false;

	while (variables[unset.v_i])
	{
		if (ft_first_node(&unset, my_envp, variables))
			continue ;
		check = ft_rest_nodes(&unset, my_envp, variables);
		if (0 == check)
			return ;
		if (unset.skip_loop)
		{
			unset.skip_loop = false;
			unset.v_i++;
			continue ;
		}
		unset.v_i++;
	}
}
