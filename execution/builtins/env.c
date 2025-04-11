/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:04:08 by fbicane           #+#    #+#             */
/*   Updated: 2025/04/07 10:14:16 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

void	ft_env(t_array *my_envp)
{
	int	i;

	i = 0;
	while (my_envp->array[i])
	{
		printf("%s\n", (char *)my_envp->array[i]);
		i++;
	}
}
