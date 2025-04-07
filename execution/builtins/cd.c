/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 18:45:52 by fbicane           #+#    #+#             */
/*   Updated: 2025/04/06 19:08:18 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

char	*ft_find_home(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "HOME=", 5))
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

void	ft_cd(char *path, char **envp)
{
	if (!path)
	{
		chdir(ft_find_home(envp));
		ft_pwd();
	}
	else
	{
		chdir(path);
		ft_pwd();
	}
}
