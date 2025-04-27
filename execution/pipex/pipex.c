/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 13:25:58 by fbicane           #+#    #+#             */
/*   Updated: 2025/04/18 16:20:00 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

int	ft_commands_count(char **commands)
{
	int	i;

	i = 0;
	while(commands[i])
		i++;
	return (i);
}

static char	**ft_find_path(t_list *my_envp)
{
	char	*path_var = NULL;

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

void	ft_exevute_command(char *command, t_list *my_envp)
{
	char	**command_arg;
	char	**paths;
	char	*path;
	int		i;

	command_arg = ft_split(command, 32);
	// TODO: protect command_arg from NULL
	paths = ft_find_path(my_envp);
	// TODO: protect paths from NULL
	path = NULL;
	i = 0;

	if (0 == access(command_arg[0], F_OK | X_OK))
	{
		execve(command_arg[0], command_arg, ft_prep_envp(my_envp));
		// TODO: protect execve
	}
	else
	{
		while (paths[i])
		{
			path = ft_concat_path(paths[i], command_arg[0]);
			if (0 == access(path, F_OK | X_OK))
			{
				free(command_arg[0]);
				command_arg[0] = path;
				execve(command_arg[0], command_arg, ft_prep_envp(my_envp));
				// TODO: protect execve
			}
			i++;
		}
	}
}

void	ft_wait_pids(t_list *pids)
{
	pid_t	pid;

	while (pids)
	{
		pid = ft_atoi((char *)pids->content);
		waitpid(pid, NULL, 0);
		pids = pids->next;
	}
}

void	ft_pipex(char **commands, t_list *my_envp)
{
	pid_t	pid;
	int		c_i; // INFO: commands_index
	int		prev_pipe[2] = {-1, -1}; // INFO: hold pipes fds
	int		fd[2];
	int		c_count; // INFO: commands count
	char	**path = ft_find_path(my_envp);
	t_list	*pids = NULL;

	if (NULL == path)
		return ; // TODO: error mssg

	c_i = 0;
	c_count = ft_commands_count(commands);

	while (commands[c_i])
	{
		if (c_i < c_count - 1)
		{
			if (-1 == pipe(fd))
				return ; // TODO: error mssg
		}
		pid = fork();
		ft_lstadd_back(&pids, ft_lstnew(ft_itoa(pid))); // INFO: save all pids
		if (0 == pid)
		{
			if (-1 != prev_pipe[0])
			{
				if (-1 == dup2(prev_pipe[0], STDIN_FILENO))
					return; // TODO: error mssg
			}
			if (c_i < c_count - 1)
			{
				if (-1 == dup2(fd[1], STDOUT_FILENO))
					return; // TODO: error mssg
			}

			if (-1 != prev_pipe[0])
				close(prev_pipe[0]);
			if (-1 != prev_pipe[1])
				close(prev_pipe[1]);

			if (c_i < c_count - 1)
			{
				close(fd[0]);
				close(fd[1]);
			}

			ft_exevute_command(commands[c_i], my_envp);
		}
		else
		{
			if (-1 != prev_pipe[0])
				close(prev_pipe[0]);
			if (-1 != prev_pipe[1])
				close(prev_pipe[1]);

			if (c_i < c_count - 1)
			{
				prev_pipe[0] = fd[0];
				prev_pipe[1] = fd[1];
			}
		}
		c_i++;
	}
	ft_wait_pids(pids); // TODO: check if it waits for pids
}
