/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 15:34:38 by fbicane           #+#    #+#             */
/*   Updated: 2025/04/18 16:57:09 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

/*typedef struct s_flag*/
/*{*/
/*	int		index;*/
/*	bool	flag_exist;*/
/*}	t_flag;*/
/**/
/**/
/*t_flag	*ft_check_flag(char **arr)*/
/*{*/
/*	int	i;*/
/*	int	j;*/
/*	t_flag	flags;*/
/**/
/*	i = 0;*/
/*	j = 1;*/
/*	while (arr[j])*/
/*	{*/
/*		if (arr[j][0] == '-')*/
/*		{*/
/*			i++;*/
/*			while (arr[j][i] == 'n' && arr[j][i])*/
/*				i++;*/
/*			if (arr[j][i])*/
/*			{*/
/*				if (j != 1)*/
/**/
/*				return (false);*/
/**/
/*			}*/
/*		}*/
/*		j++;*/
/*	}*/
/*}*/

void	ft_echo(char *rl)
{
	char **arr;
	int	i;
	int	j = 1;
	bool	new_line = true;

	arr = ft_split(rl, 32);
	while (arr[j] && arr[j][0] == '-')
	{
		i = 1;
		while (arr[j][i] == 'n' && arr[j][i])
			i++;
		if (arr[j][i])
		{
			break;
			j--;
		}
		else
			new_line = false;
		j++;
	}
	while (arr[j])
	{
		printf("%s", arr[j]);
		if (arr[j + 1])
			printf(" ");
		j++;
	}
	if (new_line)
		printf("\n");
	ft_free_arr(arr);
}

/*void	ft_echo(bool _n, char **arr)*/
/*{*/
/*	int	i;*/
/**/
/*	if (_n)*/
/*	{*/
/*		i = 2;*/
/*		while (arr[i])*/
/*		{*/
/*			printf("%s", arr[i]);*/
/*			if (arr[i + 1])*/
/*				printf(" ");*/
/*			i++;*/
/*		}*/
/*	}*/
/*	else*/
/*	{*/
/*		i = 1;*/
/*		while (arr[i])*/
/*		{*/
/*			printf("%s", arr[i]);*/
/*			if (arr[i + 1])*/
/*				printf(" ");*/
/*			i++;*/
/*		}*/
/*		printf("\n");*/
/*	}*/
/*}*/
