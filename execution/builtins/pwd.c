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

void	ft_pwd(void)
{
	char	path[PATH_MAX];
	if (getcwd(path, sizeof(path)))
		printf("%s", path);
	else
		perror("getcwd() error");

}
