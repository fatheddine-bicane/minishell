/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:44:56 by fbicane           #+#    #+#             */
/*   Updated: 2025/04/30 18:47:41 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

static int	ft_strncmp_unset(const char *s1, const char *s2, size_t n)
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
		if (!ft_strncmp_unset(envp[i], variable, len))
			return (i);
		i++;
	}
	return (-1);
}

bool	ft_find_var(t_list *my_envp, char *variable)
{
	int	i;
	char *env_ptr;

	while (my_envp)
	{
		i = 0;
		env_ptr = (char *)my_envp->content;
		while (env_ptr[i] != '=' && env_ptr[i])
			i++;
		char	str[i];
		i = 0;
		while (env_ptr[i] != '=' && env_ptr[i])
		{
			str[i] = env_ptr[i];
			i++;
		}
		str[i] = '\0';
		if (!ft_strncmp(str, variable, ft_strlen(variable)))
			return (true);
		my_envp = my_envp->next;
	}
	return (false);
}
