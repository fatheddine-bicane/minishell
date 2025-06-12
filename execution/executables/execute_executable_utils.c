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
				free_my_envp(&shell->my_envp);
				ast_free(shell->cmd); // TODO: check what type of command to know what to free
				ft_free_arr(prep_envp);
				exit(127);
			}
			// INFO: pipe
			else
			{
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
				free_my_envp(&shell->my_envp);
				ast_free(shell->cmd);
				exit(127);
			}
			else
			{
				free_my_envp(&shell->my_envp);
				shell->exit_status = 127;
			}
		}
		else
		{
			if (to_wait)
			{
				shell->exit_status = 127;
				perror(shell->cmd->u_as.exec.argv[0]);
			}
			else
			{
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
		exec.paths = ft_split("/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin", ':');
	}
	while (exec.paths[exec.i]) // INFO: checks if th command is a path
	{
		exec.path = ft_concat_path(exec.paths[exec.i], exec.com[0]);
		// NOTE: if the command is . then access sucseed and then the print error does not happen
		if (!access(exec.path, F_OK | X_OK))
		{
			free(exec.com[0]);
			exec.com[0] = exec.path;
			char **prep_envp = ft_prep_envp(shell);
			if (0 == pid)
			{
				execve(exec.com[0], exec.com, prep_envp);
				if (to_wait)
				{
					ft_free_arr(prep_envp);
					ft_free_arr(exec.paths);
					free_my_envp(&shell->my_envp);
					ast_free(shell->root_to_free);
					ft_free_arr(shell->heredocs_files);
					exit(127);
					return;
				}
				else
				{
					ft_free_arr(prep_envp);
					ft_free_arr(exec.paths);
					free_my_envp(&shell->my_envp);
					ft_free_arr(shell->heredocs_files);
					shell->exit_status = 127;
					return;
				}
			}
			else if ((0 != pid) && to_wait)
			{
				ft_free_arr(prep_envp);
				wait_child(pid, shell);
				ft_free_arr(exec.paths);
				return;
			}
			else if (0 != pid && !to_wait)
			{
				ft_free_arr(prep_envp);
				return (ft_free_arr(exec.paths));
			}
		}
		exec.i++;
		free(exec.path);
	}
	ft_free_arr(exec.paths);
	// NOTE: here is where i clean mmry if exec fails no command found
	if (0 == pid)
	{
		if (to_wait)
		{
			ast_free(shell->root_to_free);
			free_my_envp(&shell->my_envp);
			ft_free_arr(shell->heredocs_files);
			exit(127);
		}





		// this need to be outside the to_wait (dakchi li gt l anass)
		/*if (true == shell->is_pipe) // NOTE: in runed a group inside pipes*/
		/*{*/
		/*	// WARNING: double free pipex here;*/
		/*	free_pipex(&shell->pipex);*/
			/*ft_putstr_fd(RED"pipe mode on child\n"RESET, 2);*/
		/*}*/
		ft_free_arr(shell->heredocs_files);
		/*free_pipex(&shell->pipex);*/
		// free_my_envp(&shell->my_envp);
		shell->exit_status = 127;
		return;
	}
	else
	{
		if (to_wait)
		{
			shell->exit_status = 127;
		/*ft_free_arr(shell->heredocs_files);*/
			ft_putstr_fd(shell->cmd->u_as.exec.argv[0], 2);
			ft_putstr_fd(":  No such file or director\n", 2);
			/*if (true == shell->is_pipe) // WARNING: maybe not valid free*/
			/*	free_pipex(&shell->pipex);*/
			return;
		}
		ft_free_arr(shell->heredocs_files);
		/*free_pipex(&shell->pipex);*/
		shell->exit_status = 127;
		ft_putstr_fd(shell->cmd->u_as.exec.argv[0], 2);
		ft_putstr_fd(":  No such file or director\n", 2);
		return;
	}
}
