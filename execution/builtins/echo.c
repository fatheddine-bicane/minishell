/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 15:34:38 by fbicane           #+#    #+#             */
/*   Updated: 2025/06/12 15:24:54 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

static bool handl_n(char **argv, int *i) // INFO: handle -n flag
{
	int j;

	if (!argv[*i])
		return (true);
	j = 0;
	if ('-' != argv[1][j++])
		return (true);
	while ('n' == argv[1][j])
		j++;
	if (argv[1][j])
		return (true);
	(*i)++;
	return (false);
}

void ft_print_var(int len, char *variable, t_list *my_envp)
{
	t_list *tmp;

	tmp = my_envp;
	while (tmp)
	{
		if (!ft_strncmp(variable, (char *)tmp->content, len))
		{
			printf("%s", (char *)tmp->content + len + 1);
			return;
		}
		tmp = tmp->next;
	}
	if (1 == ft_strlen(variable))
		printf("$");
}

// INFO: expand the var from envp
void ft_expand_var(char *str, int *j, t_shell *shell)
{
	t_list *my_envp;
	int i;

	my_envp = shell->my_envp;
	if (1 == ft_strlen(str))
	{
		printf("$");
		(*j)++;
		return;
	}
	i = 0;
	while ('=' != str[i] && str[i])
		i++;
	ft_print_var(i - 1, str + 1, my_envp);
	printf("%s", str + i);
	(*j)++;
}

void ft_echo(t_shell *shell)
{
	int i;
	bool new_line;

	i = 1;
	new_line = handl_n(shell->cmd->u_as.exec.argv, &i);
	while (shell->cmd->u_as.exec.argv[i])
	{
		/*if ('$' == shell->cmd->u_as.exec.argv[i][0] && '?' == shell->cmd->u_as.exec.argv[i][1])*/
		/*{*/
		/*	printf("%d", shell->exit_status);*/
		/*	if (shell->cmd->u_as.exec.argv[i + 1])*/
		/*		printf(" ");*/
		/*	i++;*/
		/*	continue ;*/
		/*}*/
		/*else if ('$' == shell->cmd->u_as.exec.argv[i][0])*/
		/*{*/
		/*	ft_expand_var(shell->cmd->u_as.exec.argv[i], &i, shell);*/
		/*	if (shell->cmd->u_as.exec.argv[i + 1])*/
		/*		printf(" ");*/
		/*	continue ;*/
		/*}*/
		printf("%s", shell->cmd->u_as.exec.argv[i]);
		if (shell->cmd->u_as.exec.argv[i + 1])
			printf(" ");
		i++;
	}
	if (new_line)
		printf("\n");
	shell->exit_status = 0;
}
