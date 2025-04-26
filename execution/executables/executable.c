/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:15:18 by fbicane           #+#    #+#             */
/*   Updated: 2025/04/19 16:59:33 by fbicane          ###   ########.fr       */
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

void	ft_apply_comm(char *rl, t_list *my_envp)
{
	char **command = ft_split(rl, 32);
	int	i = 0;
	char	*path;
	char	**paths = ft_find_path(my_envp);

	if (NULL == paths)
		return;

	int	pid = fork();

	if (!access(command[0], F_OK | X_OK))
	{
		if (0 == pid)
			execve(command[0], command, ft_prep_envp(my_envp));
		else if (0 != pid)
			wait(NULL);
	}
	else
	{
		while (paths[i])
		{
			path = ft_concat_path(paths[i], command[0]);
			if (!access(path, F_OK | X_OK))
			{
				free(command[0]);
				command[0] = path;
				if (0 == pid)
				{
					execve(command[0], command, ft_prep_envp(my_envp));
					/*execv(command[0], command);*/
				}
				else if (0 != pid)
					wait(NULL);
			}
			i++;
		}
	}
}
