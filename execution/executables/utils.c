/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:02:31 by fbicane           #+#    #+#             */
/*   Updated: 2025/04/18 18:07:39 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

//this function will transform the envp from a linked list to an arr for the execve function
char **ft_prep_envp(t_list *my_envp)
{
	int		i;
	char	**arr_envp;

	i = ft_lstsize(my_envp);
	arr_envp = malloc((sizeof(char *) * (i + 1)));
	if (NULL == arr_envp)
		return (NULL);
	i = 0;
	while (my_envp)
	{
		arr_envp[i] = ft_strdup((char *)my_envp->content);
		my_envp = my_envp->next;
		i++;
	}
	arr_envp[i] = NULL;
	return (arr_envp);
}
