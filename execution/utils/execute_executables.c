/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_executables.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:16:21 by fbicane           #+#    #+#             */
/*   Updated: 2025/05/13 16:51:05 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

char	**ft_find_path(t_list *my_envp)
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

void	ft_executable(char *command, t_list *my_envp, pid_t pid, bool to_wait)
{
	char **command_args = ft_split(command, 32);
	int	i = 0;
	char	*path;
	char	**paths = ft_find_path(my_envp);

	if (NULL == paths)
		return;

	if (!access(command_args[0], F_OK | X_OK))
	{
		if (0 == pid)
			execve(command_args[0], command_args, ft_prep_envp(my_envp));
		else if (0 != pid)
			wait(NULL);
	}
	else
	{
		while (paths[i])
		{
			path = ft_concat_path(paths[i], command_args[0]);
			if (!access(path, F_OK | X_OK))
			{
				free(command_args[0]);
				command_args[0] = path;
				if (0 == pid)
					execve(command_args[0], command_args, ft_prep_envp(my_envp));
				else if ((0 != pid) && to_wait)
					waitpid(pid, NULL, 0);
			}
			i++;
		}
		if (0 == pid)
			exit(1);
	}
}
