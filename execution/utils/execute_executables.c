/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_executables.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:16:21 by fbicane           #+#    #+#             */
/*   Updated: 2025/05/29 13:50:48 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

char	**ft_find_path(t_shell *shell)
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

/*void	ft_executable(char **command_args, t_list **my_envp, pid_t pid, bool to_wait, int *exit_stat)*/
void	ft_executable(t_shell *shell, pid_t pid, bool to_wait)
{

	char **com = shell->cmd->u_as.exec.argv;

	if (0 == pid)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}

	if (('.' == com[0][0] && '/' == com[0][1]) || (ft_strchr(com[0], '/')) || ('/' == com[0][0]))
	{
		if (!access(com[0], F_OK | X_OK))
		{
			if (0 == pid)
				execve(com[0], com, ft_prep_envp(shell));
			else if ((0 != pid) && to_wait)
				waitpid(pid, NULL, 0);
		}
		else
		{
			if (0 == pid)
			{
				exit(127);
			}
			else
			{
				shell->exit_status = 127;
				perror(com[0]);
			}
		}
	}
	else
	{
		char (**paths) = ft_find_path(shell);
		int (i) = 0;
		if (NULL == paths) // INFO: protection if path is unseted
		{
			if (0 == pid)
			{
				exit(127);
			}
			else
			{
				shell->exit_status = 127;
				perror(com[0]);
			}
			return;
		}
		while (paths[i])
		{
			char (*path) = ft_concat_path(paths[i], com[0]);
			if (!access(path, F_OK | X_OK))
			{
				free(com[0]);
				com[0] = path;
				if (0 == pid)
				{
					execve(com[0], com, ft_prep_envp(shell));
					free(path);
					ft_free_arr(paths);
					exit(127);
				}
				else if ((0 != pid) && to_wait)
				{
					wait_child(pid, shell);
					/*free(path);*/
					ft_free_arr(paths);
					return ;
				}
			}
			i++;
			free(path);
		}
		ft_free_arr(paths);
		if (0 == pid)
		{
			free_my_envp(&shell->my_envp);
			exit(127);
		}
		else
		{
			shell->exit_status = 127;
			/*ft_free_arr(paths);*/
			perror(com[0]);
		}
	}
}
