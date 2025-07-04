/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:02:31 by fbicane           #+#    #+#             */
/*   Updated: 2025/06/17 21:05:20 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

//INFO: transform my_envp from list to char**
char	**ft_prep_envp(t_shell *shell)
{
	int		i;
	char	**arr_envp;
	t_list	*my_envp;

	my_envp = shell->my_envp;
	i = ft_lstsize(my_envp);
	arr_envp = malloc((sizeof(char *) * (i + 1)));
	if (NULL == arr_envp)
		return (NULL);
	i = 0;
	while (my_envp)
	{
		if (my_envp->content)
		{
			arr_envp[i] = ft_strdup((char *)my_envp->content);
			i++;
		}
		my_envp = my_envp->next;
	}
	arr_envp[i] = NULL;
	return (arr_envp);
}
