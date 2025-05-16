/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 13:25:58 by fbicane           #+#    #+#             */
/*   Updated: 2025/05/13 16:46:41 by fbicane          ###   ########.fr       */
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

void	ft_pipex(char **commands, t_list **my_envp)
{
	pid_t	pid;
	int		c_i; // INFO: commands_index
	int		prev_pipe[2] = {-1, -1}; // INFO: hold pipes fds
	int		fd[2];
	int		c_count; // INFO: commands count
	t_list	*pids = NULL;

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

			ft_exec_builtins(ft_split(commands[c_i], 32), my_envp);
			ft_executable(commands[c_i], *my_envp, pid, false);
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
