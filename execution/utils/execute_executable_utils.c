/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_executable_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 12:02:30 by fbicane           #+#    #+#             */
/*   Updated: 2025/06/05 13:47:41 by fbicane          ###   ########.fr       */
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

// static void	path_is_null(pid_t pid, t_shell *shell, t_executable *exec)
// {
// 	if (0 == pid)
// 		return (executable_error_2(shell, exec, 4));
// 	else
// 		return (executable_error_2(shell, exec, 5));
// }
//
// void	path_is_null_p(pid_t pid, t_shell *shell, t_executable *exec)
// {
// 	if (0 == pid)
// 		return (pipe_error_2(shell, 4, exec));
// 	else
// 		return (pipe_error_2(shell, 5, exec));
// }
//
// static void	comm_path_found(pid_t pid, t_shell *shell, t_executable *exec, bool to_wait)
// {
// 	free(exec->com[0]);
// 	exec->com[0] = exec->path;
// 	if (0 == pid)
// 	{
// 		execve(exec->com[0], exec->com, ft_prep_envp(shell));
// 		if (to_wait)
// 			return (executable_error_2(shell, exec, 6));
// 		return (pipe_error_2(shell, 6, exec));
// 	}
// 	else if ((0 != pid) && to_wait)
// 		return (executable_error_3(shell, exec, 7, pid));
// 	else if (0 != pid && !to_wait)
// 		return (ft_free_arr(exec->paths));
// }

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
			if (to_wait)
			{
				// executable_error(shell, 1, prep_envp);
				free_my_envp(&shell->my_envp);
				ast_free(shell->cmd); // TODO: check what type of command to know what to free
				ft_free_arr(prep_envp);
				exit(127);
			}
			// INFO: pipe
			else
			{
				// pipe_error(shell, 1, prep_envp);
				ft_free_arr(prep_envp);
				shell->exit_status = 127;
			}
		}
		else if ((0 != pid) && to_wait)
			waitpid(pid, NULL, 0);
	}

	/*-----------------------------------------------------------*/

	else // INFO: path is not valid
	{
		if (0 == pid)
		{
			if (to_wait)
			{
				// executable_error(shell, 2, NULL);
				free_my_envp(&shell->my_envp);
				ast_free(shell->cmd);
				exit(127);
			}
			else
			{
				// pipe_error(shell, 2, NULL);
				free_my_envp(&shell->my_envp);
				shell->exit_status = 127;
			}
		}
		else
		{
			if (to_wait)
			{
				// executable_error(shell, 3, NULL);
				shell->exit_status = 127;
				perror(shell->cmd->u_as.exec.argv[0]);
			}
			else
			{
				// pipe_error(shell, 3, NULL);
				shell->exit_status = 127;
				perror(shell->cmd->u_as.exec.argv[0]);
			}
		}
	}
}

void	command_is_not_path(pid_t pid, t_shell *shell, bool to_wait)
{
	t_executable	exec;

	exec.com = shell->cmd->u_as.exec.argv;
	exec.paths = ft_find_path(shell);
	exec.i = 0;
	if (NULL == exec.paths) // INFO: protection if path is unseted
	{
		if (to_wait)
		{
			if (0 == pid)
			{
				free_my_envp(&shell->my_envp);
				ast_free(shell->cmd);
				exit(127);
				// return (executable_error_2(shell, exec, 4));
			}
			else
			{
				ft_free_arr(exec.paths);
				shell->exit_status = 127;
				ft_putstr_fd(shell->cmd->u_as.exec.argv[0], 2);
				ft_putstr_fd(":  No such file or director\n", 2);
				return;

				// return (executable_error_2(shell, exec, 5));
			}
			// return (path_is_null(pid, shell, &exec));
		}
		else
		{
			if (0 == pid)
			{
				free_my_envp(&shell->my_envp);
				shell->exit_status = 127;
				return;
				// return (pipe_error_2(shell, 4, exec));
			}
			else
			{
				ft_free_arr(exec.paths);
				ft_putstr_fd(shell->cmd->u_as.exec.argv[0], 2);
				ft_putstr_fd(":  No such file or director\n", 2);
				shell->exit_status = 127;
				return;
				// return (pipe_error_2(shell, 5, exec));
			}
		}

		// return (path_is_null_p(pid, shell, &exec));
	}
	while (exec.paths[exec.i]) // INFO: checks if th command is a path
	{
		exec.path = ft_concat_path(exec.paths[exec.i], exec.com[0]);
		if (!access(exec.path, F_OK | X_OK))
		{
			free(exec.com[0]);
			exec.com[0] = exec.path;
			if (0 == pid)
			{
				execve(exec.com[0], exec.com, ft_prep_envp(shell));
				if (to_wait)
				{
					free(exec.path);
					ft_free_arr(exec.paths);
					free_my_envp(&shell->my_envp);
					ast_free(shell->cmd);
					exit(127);
					return;
					// return (executable_error_2(shell, exec, 6));
				}
				else
				{
					free(exec.path);
					ft_free_arr(exec.paths);
					free_my_envp(&shell->my_envp);
					shell->exit_status = 127;
					return;
					// return (pipe_error_2(shell, 6, exec));
				}
			}
			else if ((0 != pid) && to_wait)
			{
				wait_child(pid, shell);
				ft_free_arr(exec.paths);
				return;
				// return (executable_error_3(shell, &exec, 7, pid));
			}
			else if (0 != pid && !to_wait)
				return (ft_free_arr(exec.paths));

			// return (comm_path_found(pid, shell, &exec, to_wait));
		}
		exec.i++;
		free(exec.path);
	}
	ft_free_arr(exec.paths);
	if (0 == pid)
	{
		if (to_wait)
		{
			ast_free(shell->cmd);
			free_my_envp(&shell->my_envp);
			exit(127);
			// return (executable_error_3(shell,&exec, 8, pid));
		}
		free_my_envp(&shell->my_envp);
		shell->exit_status = 127;
		return;
		// return (pipe_error_3(shell, &exec, 7, 0));
	}
	else
	{
		if (to_wait)
		{
			shell->exit_status = 127;
			ft_putstr_fd(shell->cmd->u_as.exec.argv[0], 2);
			ft_putstr_fd(":  No such file or director\n", 2);
			return;
			// return (executable_error_3(shell,&exec, 9, pid));
		}
		shell->exit_status = 127;
		ft_putstr_fd(shell->cmd->u_as.exec.argv[0], 2);
		ft_putstr_fd(":  No such file or director\n", 2);
		return;
		// return (pipe_error_3(shell, &exec, 8, 0));
	}
}
