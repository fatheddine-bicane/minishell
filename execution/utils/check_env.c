/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 20:25:53 by fbicane           #+#    #+#             */
/*   Updated: 2025/04/10 20:30:58 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

bool	ft_strcmp(char *value, char *envp_l)
{
	int (i) = 0;

	while (envp_l[i] != '=')
		i++;
	char (str[i]);
	i = 0;
	while (envp_l[i] != '=')
		str[i] = envp_l[i];
	str[i] = '\0';
	if (!ft_strncmp(value, str, ft_strlen(value)))
		return (true);
	else
		return (false);
}

void	ft_check_env(t_list **envp, char *value)
{
	
}
