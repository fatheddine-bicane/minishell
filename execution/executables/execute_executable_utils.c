/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_executable_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 12:02:30 by fbicane           #+#    #+#             */
/*   Updated: 2025/06/11 22:32:56 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

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

static void	command_is_path_utils(t_shell *shell, pid_t pid, bool to_wait, char **prep_envp)
{
	char	**com;

	com = shell->cmd->u_as.exec.argv;
	if (0 == pid)
	{
		prep_envp = ft_prep_envp(shell);
		execve(com[0], com, prep_envp);
		if (to_wait)
			executable_error(shell, 1, prep_envp);
		// INFO: pipe
		return (executable_error(shell, 2, prep_envp));
	}
	else if ((0 != pid) && to_wait)
		wait_child(pid, shell);
}

void	command_is_path(pid_t pid, t_shell *shell, bool to_wait)
{
	char	**com;
	char	**prep_envp;

	com = shell->cmd->u_as.exec.argv;
	prep_envp = NULL;
	if (!access(com[0], F_OK | X_OK)) // INFO: checks if the path is valid
		command_is_path_utils(shell, pid, to_wait, prep_envp);
	else // INFO: path is not valid
	{
		if (0 == pid)
		{
			if (to_wait)
				executable_error(shell, 3, prep_envp);
			return (executable_error_2(shell, 4));
		}
		else
		{
			if (to_wait)
				return (executable_error_2(shell, 5));
			return (executable_error_2(shell, 6));
		}
	}
}

// static void	command_is_not_path_utils(pid_t pid, t_shell *shell, bool to_wait, t_executable *exec)
// {
// 	exec->path = ft_concat_path(exec->paths[exec->i], exec->com[0]);
// 	if (!access(exec->path, F_OK | X_OK))
// 	{
// 		free(exec->com[0]);
// 		exec->com[0] = exec->path;
// 		char **(prep_envp) = ft_prep_envp(shell);
// 		if (0 == pid)
// 		{
// 			execve(exec->com[0], exec->com, prep_envp);
// 			if (to_wait)
// 				executable_error_3(shell, exec, 7, pid, prep_envp);
// 			return (executable_error_3(shell, exec, 8, pid, prep_envp));
// 		}
// 		else if ((0 != pid) && to_wait)
// 			return (executable_error_4(shell, exec, 10, pid, prep_envp));
// 		else if (0 != pid && !to_wait)
// 			return (executable_error_4(shell, exec, 11, pid, prep_envp));
// 	}
// }

void	command_is_not_path(pid_t pid, t_shell *shell, bool to_wait)
{
	t_executable	exec;

	exec.com = shell->cmd->u_as.exec.argv;
	exec.paths = ft_find_path(shell);
	exec.i = 0;
	if (NULL == exec.paths) // INFO: protection if path is unseted
		exec.paths = ft_split("/nothing", ':');
	// command_is_not_path_utils(pid, shell, to_wait, &exec);
	while (exec.paths[exec.i]) // INFO: checks if th command is a path
	{
		// command_is_not_path_utils(pid, shell, to_wait, &exec);
		exec.path = ft_concat_path(exec.paths[exec.i], exec.com[0]);
		if (!access(exec.path, F_OK | X_OK))
		{
			free(exec.com[0]);
			exec.com[0] = exec.path;
			char **(prep_envp) = ft_prep_envp(shell);
			if (0 == pid)
			{
				execve(exec.com[0], exec.com, prep_envp);
				if (to_wait)
					executable_error_3(shell, &exec, 7, pid, prep_envp);
				return (executable_error_3(shell, &exec, 8, pid, prep_envp));
			}
			else if ((0 != pid) && to_wait)
				return (executable_error_4(shell, &exec, 10, pid, prep_envp));
			else if (0 != pid && !to_wait)
				return (executable_error_4(shell, &exec, 11, pid, prep_envp));
		}
		exec.i++;
		free(exec.path);
	}
	ft_free_arr(exec.paths);
	// NOTE: here is where i clean mmry if exec fails no command found
	if (0 == pid)
	{
		if (to_wait)
			executable_error_4(shell, &exec, 12, pid, NULL);
		return (executable_error_4(shell, &exec, 13, pid, NULL));
	}
	else
	{
		if (to_wait)
			return (executable_error_5(shell, 14));
		return (executable_error_5(shell, 15));
	}
}
