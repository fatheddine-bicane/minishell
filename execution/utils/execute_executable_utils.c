/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_executable_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 12:02:30 by fbicane           #+#    #+#             */
/*   Updated: 2025/06/01 13:02:31 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

static char	**ft_find_path(t_shell *shell)
{
	char	*path_var = NULL;
	t_list *my_envp;

	my_envp = shell->my_envp;

	while (my_envp)
	{
		if (!ft_strncmp((char *)my_envp->content, "PATH=", 5))
		{
			path_var = (char *)my_envp->content;
			break;
		}
		my_envp = my_envp->next;
	}
	if (NULL == path_var)
		return (NULL);
	char **(paths) = ft_split(path_var + 5, ':');
	return (paths);
}

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

static void	path_is_null(pid_t pid, t_shell *shell, t_executable *exec)
{
		if (0 == pid)
			return (executable_error_2(shell, exec, 4));
		else
			return (executable_error_2(shell, exec, 5));
}

static void	comm_path_found(pid_t pid, t_shell *shell, t_executable *exec, bool to_wait)
{
	free(exec->com[0]);
	exec->com[0] = exec->path;
	if (0 == pid)
	{
		execve(exec->com[0], exec->com, ft_prep_envp(shell));
		return (executable_error_2(shell, exec, 6));
	}
	else if ((0 != pid) && to_wait)
		return (executable_error_3(shell, exec, 7, pid));
}

void	command_is_path(pid_t pid, t_shell *shell, bool to_wait)
{
	char	**com;
	char	**prep_envp;

	com = shell->cmd->u_as.exec.argv;
	if (!access(com[0], F_OK | X_OK)) // INFO: checks if the path is valid
	{
		if (0 == pid)
		{
			prep_envp = ft_prep_envp(shell);
			execve(com[0], com, prep_envp);
			executable_error(shell, 1, prep_envp);
		}
		else if ((0 != pid) && to_wait)
			waitpid(pid, NULL, 0);
	}
	else
	{
		if (0 == pid)
			executable_error(shell, 2, NULL);
		else
			executable_error(shell, 3, NULL);
	}
}

void	command_is_not_path(pid_t pid, t_shell *shell, bool to_wait)
{
	t_executable	exec;

	exec.com = shell->cmd->u_as.exec.argv;
	exec.paths = ft_find_path(shell);
	exec.i = 0;
	if (NULL == exec.paths) // INFO: protection if path is unseted
		return (path_is_null(pid, shell, &exec));
	while (exec.paths[exec.i]) // INFO: checks if th command is a path
	{
		exec.path = ft_concat_path(exec.paths[exec.i], exec.com[0]);
		if (!access(exec.path, F_OK | X_OK))
			return (comm_path_found(pid, shell, &exec, to_wait));
		exec.i++;
		free(exec.path);
	}
	ft_free_arr(exec.paths);
	if (0 == pid)
		return (executable_error_3(shell,&exec, 8, pid));
	else
		return (executable_error_3(shell,&exec, 9, pid));
}
