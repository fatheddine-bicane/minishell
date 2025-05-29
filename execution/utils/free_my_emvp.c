/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_my_emvp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 18:23:39 by fbicane           #+#    #+#             */
/*   Updated: 2025/05/28 18:38:33 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

void	free_my_envp(t_list **my_envp)
{
	t_list *head = *my_envp;
	t_list	*to_free;

	while (head)
	{
		to_free = head;
		head = head->next;
		free(to_free->content);
		free(to_free);
	}
}
