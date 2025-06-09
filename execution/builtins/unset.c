/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:55:55 by fbicane           #+#    #+#             */
/*   Updated: 2025/06/01 00:26:51 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

// INFO: check first node
static bool	ft_first_node(t_unset *unset, t_shell *shell)
{
	unset->env_cont = (char *)shell->my_envp->content;
	unset->i = 0;
	while (unset->env_cont[unset->i] && unset->env_cont[unset->i] != '=')
		unset->i++;
	if (!ft_strncmp(unset->env_cont,
			shell->cmd->u_as.exec.argv[unset->v_i], unset->i))
	{
		unset->env_to_del = shell->my_envp;
		shell->my_envp = shell->my_envp->next;
		free(unset->env_to_del->content);
		free(unset->env_to_del);
		return (true);
	}
	return (false);
}

// INFO: check the rest nodes
static int	ft_rest_nodes(t_unset *unset, t_shell *shell)
{
	unset->tmp_envp = shell->my_envp;
	while (unset->tmp_envp)
	{
		if (NULL == unset->tmp_envp->next)
			return (0);
		unset->env_cont = (char *)unset->tmp_envp->next->content;
		unset->i = 0;
		while (unset->env_cont[unset->i] && unset->env_cont[unset->i] != '=')
			unset->i++;
		if (!ft_strncmp(unset->env_cont,
				shell->cmd->u_as.exec.argv[unset->v_i], unset->i))
		{
			unset->env_to_del = unset->tmp_envp->next;
			unset->tmp_envp->next = unset->tmp_envp->next->next;
			free(unset->env_to_del->content);
			free(unset->env_to_del);
			unset->skip_loop = true;
			break ;
		}
		unset->tmp_envp = unset->tmp_envp->next;
	}
	return (2);
}

void	ft_unset(t_shell *shell)
{
	t_unset	unset;
	int		check;

	if (NULL == shell->cmd->u_as.exec.argv)
		return ;
	unset.v_i = 1;
	unset.skip_loop = false;
	while (shell->cmd->u_as.exec.argv[unset.v_i])
	{
		if (ft_first_node(&unset, shell))
			continue ;
		check = ft_rest_nodes(&unset, shell);
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
