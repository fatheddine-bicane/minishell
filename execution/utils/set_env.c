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

//INFO: this functions set a custum envp in alinked list so it can be modified later
t_list *ft_set_env(char **envp)
{
	t_list	*c_envp = NULL;
	int		i;

	i = 0;
	while (envp[i])
	{
		ft_lstadd_back(&c_envp, ft_lstnew(ft_strdup((char *)envp[i])));
		i++;
	}
	return (c_envp);
}
