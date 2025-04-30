/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:55:55 by fbicane           #+#    #+#             */
/*   Updated: 2025/04/23 09:46:51 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

int	ft_strncmp_(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	if (!s1 && !s2)
		return (0);
	i = 0;
	while ((s1[i] != 0 || s2[i] != 0 || s1[i] != '=') && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int	ft_find_variable(char **envp, char *variable)
{
	int	i;
	int	len;

	len = ft_strlen(variable);
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp_(envp[i], variable, len))
			return (i);
		i++;
	}
	return (-1);
}

bool	ft_find_var(t_list *my_envp, char *variable)
{
	int	i;
	char *env_ptr;

	while (my_envp)
	{
		i = 0;
		env_ptr = (char *)my_envp->content;
		while (env_ptr[i] != '=' && env_ptr[i])
			i++;
		char	str[i];
		i = 0;
		while (env_ptr[i] != '=' && env_ptr[i])
		{
			str[i] = env_ptr[i];
			i++;
		}
		str[i] = '\0';
		if (!ft_strncmp(str, variable, ft_strlen(variable)))
			return (true);
		my_envp = my_envp->next;
	}
	return (false);
}

bool	ft_first_node(t_unset *unset, t_list **my_envp, char **variables)
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

int	ft_rest_nodes(t_unset *unset, t_list **my_envp, char **variables)
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
	/*if (unset->skip_loop)*/
	/*{*/
	/*	unset->skip_loop = false;*/
	/*	unset->v_i++;*/
	/*	return (1);*/
	/*}*/
	return (2);
}

void	ft_unset(t_list **my_envp, char **variables)
{
	/*t_list	*env_to_del;*/
	/*t_list	*tmp_envp;*/
	/*char	*env_cont;*/
	/*int		i;*/
	/*int		v_i; // INFO: variables index*/
	/*bool	skip_loop;*/
	t_unset	unset;
	int		check;

	if (NULL == variables)
		return;

	unset.v_i = 1;
	unset.skip_loop = false;

	while (variables[unset.v_i])
	{
		/*// INFO: check first node*/
		/*unset.env_cont = (char *)(*my_envp)->content;*/
		/*unset.i = 0;*/
		/**/
		/*while (unset.env_cont[unset.i] && unset.env_cont[unset.i] != '=')*/
		/*	unset.i++;*/
		/**/
		/*if (!ft_strncmp(unset.env_cont, variables[unset.v_i], unset.i))*/
		/*{*/
		/*	unset.env_to_del = (*my_envp);*/
		/*	(*my_envp) = (*my_envp)->next;*/
		/*	(void)unset.env_to_del;*/
		/*	//free(env_to_del->content);*/
		/*	free(unset.env_to_del);*/
		/*	continue ;*/
		/*}*/
		if (ft_first_node(&unset, my_envp, variables))
			continue ;

		/*// INFO: check the rest nodes*/
		/*unset.tmp_envp = (*my_envp);*/
		/*while (unset.tmp_envp)*/
		/*{*/
		/*	if (NULL == unset.tmp_envp->next)*/
		/*		return;*/
		/**/
		/*	unset.env_cont = (char *)unset.tmp_envp->next->content;*/
		/*	unset.i = 0;*/
		/**/
		/*	while (unset.env_cont[unset.i] && unset.env_cont[unset.i] != '=')*/
		/*		unset.i++;*/
		/**/
		/*	if (!ft_strncmp(unset.env_cont, variables[unset.v_i], unset.i))*/
		/*	{*/
		/*		unset.env_to_del = unset.tmp_envp->next;*/
		/*		unset.tmp_envp->next = unset.tmp_envp->next->next;*/
		/*		(void)unset.env_to_del;*/
		/*		//free(env_to_del->content);*/
		/*		free(unset.env_to_del);*/
		/*		unset.skip_loop = true;*/
		/*		break ;*/
		/*	}*/
		/**/
		/*	unset.tmp_envp = unset.tmp_envp->next;*/
		/*}*/
		check = ft_rest_nodes(&unset, my_envp, variables);
		if (0 == check)
			return ;
		/*else if (1 == check)*/
		/*	continue ;*/
		if (unset.skip_loop)
		{
			unset.skip_loop = false;
			unset.v_i++;
			continue ;
		}
		unset.v_i++;
	}
}
