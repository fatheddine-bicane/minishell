/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:35:43 by fbicane           #+#    #+#             */
/*   Updated: 2025/05/16 15:53:14 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

char	**ft_split_variable(char *variable)
{
	char	**res;
	char	*value;
	int		i;

	i = 0;
	while ('=' != variable[i] && variable[i])
		i++;
	char (key[i]);
	i = 0;
	while ('=' != variable[i] && variable[i])
	{
		key[i] = variable[i];
		i++;
	}
	key[i] = '\0';
	value = ft_strchr(variable, '=');
	res = malloc(sizeof(char *) * 3);
	if (!res)
		return (NULL);
	res[0] = ft_strdup(key);
	res[1] = ft_strdup(value + 1);
	res[2] = NULL;
	return (res);
}
