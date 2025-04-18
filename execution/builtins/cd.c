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


void	ft_cd(char *path)
{
	if (!path)
	{
		errno = chdir(getenv("HOME"));
		if (errno == -1)
			errno = ENOENT;
		ft_pwd();
	}
	else
	{
		errno = chdir(path);
		if (errno == -1)
			errno = ENOENT;
		ft_pwd();
	}
}
