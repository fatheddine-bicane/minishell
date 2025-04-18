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

/*void	ft_env(char **envp)*/
/*{*/
/*	int	i;*/
/**/
/*	i = 0;*/
/*	while (envp[i])*/
/*	{*/
/*		printf("%s\n", envp[i]);*/
/*		i++;*/
/*	}*/
/*}*/

 void	ft_env(t_list *my_envp)
{
	int	i;

	i = 0;
	while (my_envp)
	{
		printf("%s\n", (char *)my_envp->content);
		my_envp = my_envp->next;
	}
}
