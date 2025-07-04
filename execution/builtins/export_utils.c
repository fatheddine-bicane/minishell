/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 15:38:03 by fbicane           #+#    #+#             */
/*   Updated: 2025/06/01 00:22:54 by fbicane          ###   ########.fr       */
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

void	ft_export_utils_1(t_shell *shell, char *variable)
{
	t_list	**my_envp;

	my_envp = &shell->my_envp;
	if (ft_equal_in_var(variable))
		ft_update_var(my_envp, variable);
}
