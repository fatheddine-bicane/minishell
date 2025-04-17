/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_envp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 15:29:03 by fbicane           #+#    #+#             */
/*   Updated: 2025/04/13 18:06:38 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

static void	ft_free(char **arr_s)
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
}

static int	ft_envs_len(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

/*int	ft_find_variable(char **my_envp, )*/
/*{*/
/*	int	i;*/
/**/
/*	i = 0;*/
/**/
/*}*/

char	**ft_add_variable(char **my_envp, char *variable)
{
	char	**new_envp;
	int		i;

	new_envp = malloc(sizeof(char *) * ft_envs_len(my_envp) + 1);
	if (NULL == new_envp)
		return (NULL);
	i = 0;
	while (my_envp[i])
	{
		new_envp[i] = ft_strdup(my_envp[i]);
		i++;
	}
	new_envp[i++] = ft_strdup(variable);
	new_envp[i] = NULL;
	ft_free(my_envp);
	return (new_envp);
}

char	**ft_set_my_envp(char **envp)
{
	char	**my_envp;
	int		i;

	my_envp = malloc(sizeof(char *) * ft_envs_len(envp));
	if (NULL == my_envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		my_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	my_envp[i] = NULL;
	return(my_envp);
}
