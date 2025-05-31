/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:27:43 by fbicane           #+#    #+#             */
/*   Updated: 2025/05/31 18:59:55 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

static bool	ft_variable_exist(t_shell *shell, char *varaible)
{
	int		i;
	t_list	*tmp;

	i = 0;
	while (varaible[i] && '=' != varaible[i])
		i++;

	if ('+' == varaible[i - 1])
		i--;
	tmp = shell->my_envp;
	while (tmp)
	{
		if (!ft_strncmp(tmp->content, varaible, i))
			return (true);
		tmp = tmp->next;
	}
	return (false);
}

static bool	ft_valid_argument(char *variable)
{
	int	i;

	i = 0;
	if (!ft_isalpha(variable[i]) && '_' != variable[i])
		return (false);
	i++;
	while ('=' != variable[i] && variable[i])
	{
		if ('=' == variable[i])
			break ;
		if (!ft_isalnum(variable[i]))
			return (false);
		i++;
	}
	return (true);
}

static void	ft_sort_myenvp(t_shell *shell)
{
	char	**envp_sort;
	char	*tmp;
	int		i;
	int		j;

	envp_sort = ft_prep_envp(shell);
	i = -1;
	while(envp_sort[++i])
	{
		j = i + 1;
		while (envp_sort[j])
		{
			if (0 < ft_strncmp(envp_sort[i], envp_sort[j], ft_strlen(envp_sort[i])))
			{
				tmp = envp_sort[i];
				envp_sort[i] = envp_sort[j];
				envp_sort[j] = tmp;
			}
			j++;
		}
	}
	i = -1;
	while (envp_sort[++i])
		printf("%s\n", envp_sort[i]);
	ft_free_arr(envp_sort);
}

void	ft_export(t_shell *shell)
{
	int	vars_i;

	if (!shell->cmd->u_as.exec.argv[1]) // INFO: export with no argumets
		ft_sort_myenvp(shell);
	else
	{
		vars_i = 1;
		while (shell->cmd->u_as.exec.argv[vars_i])
		{
			if (!ft_valid_argument(shell->cmd->u_as.exec.argv[vars_i])) // INFO: checking if var name is valid syntax
			{
				export_error(shell, &vars_i);
				continue;
			}
			if (ft_variable_exist(shell, shell->cmd->u_as.exec.argv[vars_i])) // INFO: checking if var name exist in my_envp
				ft_export_utils_1(shell, shell->cmd->u_as.exec.argv[vars_i]);
			else
				ft_lstadd_back(&shell->my_envp,
					ft_lstnew(ft_strdup(shell->cmd->u_as.exec.argv[vars_i])));
			vars_i++;
		}
	}
	shell->exit_status = 0;
}
