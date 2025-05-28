/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 21:38:34 by fbicane           #+#    #+#             */
/*   Updated: 2025/04/06 21:42:47 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

void	ft_pwd(int *exit_status)
{
	char	path[PATH_MAX];
	if (getcwd(path, sizeof(path)))
	{
		printf("%s\n", path);
		(*exit_status) = 0;
	}
	else
	{
		perror("getcwd() error");
		(*exit_status) = 1;
	}
}
