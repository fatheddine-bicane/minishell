/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 15:34:38 by fbicane           #+#    #+#             */
/*   Updated: 2025/04/30 18:54:20 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

void	ft_handl_n(char **arr, int *j, bool *new_line) // INFO: handle -n flag
{
	int	i;

	i = 0;
	while ('-' == arr[*j][0] && arr[*j])
	{
		i = 1;
		while ('n' == arr[*j][i] && arr[*j][i])
			i++;
		if (arr[*j][i])
		{
			(*j)--;
			break;
		}
		else
			(*new_line) = false;
		(*j)++;
	}
}

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
	if (1 == ft_strlen(variable))
		printf("$");
}

void	ft_expand_var(char *str, int *j, t_list *my_envp)// INFO: expand the var from envp
{
	int	i;

	if (1 == ft_strlen(str))
	{
		printf("$");
		(*j)++;
		return ;
	}
	i = 0;
	while ('=' != str[i] && str[i])
		i++;
	ft_print_var(i - 1, str + 1, my_envp);
	printf("%s", str + i);
	(*j)++;
}

void	ft_echo(char **echo_arg, t_list *my_envp, int *exit_stat)
{
	int		i;
	bool	new_line;

	i = 1;
	new_line = true;
	ft_handl_n(echo_arg, &i, &new_line);
	while (echo_arg[i])
	{

		printf("argv to print   %s\n", echo_arg[i]);
		if ('$' == echo_arg[i][0] && '?' == echo_arg[i][1])
		{
			printf("%d", (*exit_stat));
			if (echo_arg[i + 1])
				printf(" ");
			i++;
			continue ;
		}
		else if ('$' == echo_arg[i][0])
		{
			ft_expand_var(echo_arg[i], &i, my_envp);
			if (echo_arg[i + 1])
				printf(" ");
			continue ;
		}
		printf("%s", echo_arg[i]);
		if (echo_arg[i + 1])
			printf(" ");
		i++;
	}
	if (new_line)
		printf("\n");
	ft_free_arr(echo_arg);
	(*exit_stat) = 0;
}
