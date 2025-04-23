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

void	ft_print_var(int len, char *variable, t_list *my_envp)
{
	while (my_envp)
	{
		if (!ft_strncmp(variable, (char *)my_envp->content, len))
		{
			printf("%s", (char *)my_envp->content + len + 1);
			return;
		}
		my_envp = my_envp->next;
	}
}

void	ft_echo(char *rl, t_list *my_envp)
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

	if (arr[j][0] == '$')
	{
		i = 0;
		while (arr[j][i] != '=' && arr[j][i])
			i++;
		ft_print_var(i - 1, arr[j] + 1, my_envp);
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
