/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:43:14 by fbicane           #+#    #+#             */
/*   Updated: 2025/04/18 16:43:41 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

void	ft_free_arr(char **arr_s)
{
	int	i;

	i = 0;
	if (!arr_s)
		return ;
	while (arr_s[i] != 0)
	{
		free(arr_s[i]);
		i++;
	}
	free (arr_s);
	arr_s = NULL;
}

void	free_my_envp(t_list **my_envp)
{
	t_list	*head;
	t_list	*to_free;

	head = (*my_envp);
	while (head)
	{
		to_free = head;
		head = head->next;
		free(to_free->content);
		free(to_free);
	}
}
