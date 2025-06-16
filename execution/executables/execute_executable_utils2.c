/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_executable_utils2.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 11:05:51 by fbicane           #+#    #+#             */
/*   Updated: 2025/06/16 11:14:12 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

static char	*ft_concat_path(char *arr2, char *command)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = malloc(ft_strlen(arr2) + ft_strlen(command) + 2);
	while (arr2[i])
		str[j++] = arr2[i++];
	i = 0;
	str[j++] = '/';
	while (command[i])
		str[j++] = command[i++];
	str[j] = '\0';
	return (str);
}

static char	**ft_find_path(t_shell *shell)
{
	char	*path_var;
	t_list	*my_envp;

	my_envp = shell->my_envp;
	path_var = NULL;
	while (my_envp)
	{
		if (!ft_strncmp((char *)my_envp->content, "PATH=", 5))
		{
			path_var = (char *)my_envp->content;
			break ;
		}
		my_envp = my_envp->next;
	}
	if (NULL == path_var)
		return (NULL);
	char **(paths) = ft_split(path_var + 5, ':');
	return (paths);
}

static void	command_is_not_path_utils(pid_t pid, t_shell *shell,
	bool to_wait, t_executable *exec)
{
	ft_free_arr(exec->paths);
	// NOTE: here is where i clean mmry if exec fails no command found
	if (0 == pid)
	{
		if (to_wait)
			executable_error_4(shell, exec, 12, pid);
		return (executable_error_4(shell, exec, 13, pid));
	}
	else
	{
		if (to_wait)
			return (executable_error_5(shell, 14));
		return (executable_error_5(shell, 15));
	}
}

static char	**command_is_not_path_utils2(t_shell *shell,
	t_executable *exec, int flag)
{
	char	**prep_envp;

	if (1 == flag)
	{
		exec->com = shell->cmd->u_as.exec.argv;
		exec->paths = ft_find_path(shell);
		exec->i = 0;
		if (NULL == exec->paths) // INFO: protection if path is unseted
			exec->paths = ft_split("/nothing", ':');
		return (NULL);
	}
	else if (2 == flag)
	{
		free(exec->com[0]);
		exec->com[0] = exec->path;
		prep_envp = ft_prep_envp(shell);
		return (prep_envp);
	}
	return (NULL);
}

void	command_is_not_path(pid_t pid, t_shell *shell, bool to_wait)
{
	t_executable	exec;

	command_is_not_path_utils2(shell, &exec, 1);
	while (exec.paths[exec.i]) // INFO: checks if th command is a path
	{
		exec.path = ft_concat_path(exec.paths[exec.i], exec.com[0]);
		if (!access(exec.path, F_OK | X_OK))
		{
			exec.penvp = command_is_not_path_utils2(shell, &exec, 2);
			if (0 == pid)
			{
				execve(exec.com[0], exec.com, exec.penvp);
				if (to_wait)
					executable_error_3(shell, &exec, 7, pid);
				return (executable_error_3(shell, &exec, 8, pid));
			}
			else if ((0 != pid) && to_wait)
				return (executable_error_4(shell, &exec, 10, pid));
			else if (0 != pid && !to_wait)
				return (executable_error_4(shell, &exec, 11, pid));
		}
		exec.i++;
		free(exec.path);
	}
	command_is_not_path_utils(pid, shell, to_wait, &exec);
}
