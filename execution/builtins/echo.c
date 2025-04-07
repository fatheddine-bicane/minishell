/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 15:34:38 by fbicane           #+#    #+#             */
/*   Updated: 2025/04/06 16:03:00 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

void	ft_echo(bool _n, char **arr)
{
	int	i;

	if (_n)
	{
		i = 2;
		while (arr[i])
		{
			printf("%s", arr[i]);
			if (arr[i + 1])
				printf(" ");
			i++;
		}
	}
	else
	{
		i = 1;
		while (arr[i])
		{
			printf("%s", arr[i]);
			if (arr[i + 1])
				printf(" ");
			i++;
		}
		printf("\n");
	}
}
