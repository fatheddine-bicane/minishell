/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:48:49 by fbicane           #+#    #+#             */
/*   Updated: 2025/04/10 17:24:58 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

t_list *ft_set_env(char **envp)
{
	t_list	*c_envp;
	int		i;

	i = 0;
	while (envp[i])
	{
		ft_lstadd_back(&c_envp, ft_lstnew((char *)envp[i]));
		i++;
	}
	return (c_envp);
}

t_array	*ft_set_env_(char **envp)
{
	t_array *my_envp;
	int		i;

	my_envp = ft_init_arr();
	if (NULL == my_envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		if (my_envp->capacity == my_envp->len)
			my_envp = ft_resize(&my_envp);
		my_envp->array[i] = ft_strdup(envp[i]);
		i++;
		my_envp->len++;
	}
	return (my_envp);
}
