/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:55:55 by fbicane           #+#    #+#             */
/*   Updated: 2025/04/12 16:24:36 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

int	ft_strncmp_(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	if (!s1 && !s2)
		return (0);
	i = 0;
	while ((s1[i] != 0 || s2[i] != 0 || s1[i] != '=') && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int	ft_find_variable(char **envp, char *variable)
{
	int	i;
	int	len;

	len = ft_strlen(variable);
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp_(envp[i], variable, len))
			return (i);
		i++;
	}
	return (-1);
}

/*static void	ft_free(char **arr_s)*/
/*{*/
/*	int	i;*/
/**/
/*	i = 0;*/
/*	if (!arr_s)*/
/*		return ;*/
/*	while (arr_s[i])*/
/*	{*/
/*		free(arr_s[i]);*/
/*		i++;*/
/*	}*/
/*	free (arr_s);*/
/*}*/

char **ft_unset(char **en, char *variable)
{
	(void)variable;
	/*int	index;*/
	char **envp;

	/*index = ft_find_variable((*my_envp), variable);*/
	/*printf("%d\n", index);*/
	/*ft_free(en);*/
	(void)en;
	envp = malloc(sizeof(char *) * 4);
	envp[0] = ft_strdup("tdasjdasjd");
	envp[1] = ft_strdup("haaa");
	envp[2] = ft_strdup("hahahsjsjs");
	envp[3] = NULL;
	return (envp);

	/*free((*my_envp)->array[index]);*/
	/*(*my_envp)->array[index] = ft_strdup("waaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");*/
	/*(*my_envp)->len--;*/
}
