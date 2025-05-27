/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_executables.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:16:21 by fbicane           #+#    #+#             */
/*   Updated: 2025/05/23 17:37:30 by fbicane          ###   ########.fr       */
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

char	*find_executable_cwd(char *cmd)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)))
		return (ft_strjoin(cwd, cmd));
	else
	{
		// TODO: error mssg (protect getcwd)
	}
	return (NULL);

}

void	ft_executable(char *command, t_list *my_envp, pid_t pid, bool to_wait)
{
	char **command_args = ft_split(command, 32);
	int	i = 0;
	char	*path;
	char	**paths = ft_find_path(my_envp);

	if (NULL == paths)
		return;

	if (0 == pid)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}

	/*printf ("%s\n", command_args[0]);*/
	if ('.' == command_args[0][0])
	{
		path = find_executable_cwd(command_args[0] + 1);
		/*if (!access(path, F_OK | X_OK))*/

		if (!access(command_args[0], F_OK | X_OK))
		{
			printf("wa ana hnaya\n");
			if (0 == pid)
			{
				execve(command_args[0], command_args, ft_prep_envp(my_envp));
			}
			else if ((0 != pid) && to_wait)
				waitpid(pid, NULL, 0);
		}
		else
		{
			if (0 == pid)
				exit(1);
			printf("command not found walo\n");
		}
	}
	else if (!access(command_args[0], F_OK | X_OK))
	{
		if (0 == pid)
		{
			/*printf("hna execute same directory %s\n", command_args[0]);*/
			execve(command_args[0], command_args, ft_prep_envp(my_envp));
		}
		else if ((0 != pid) && to_wait)
			waitpid(pid, NULL, 0);
	}
	else
	{
		/*printf("else %s\n", command);*/
		while (paths[i])
		{
			/*if (0 == pid)*/
			/*	printf("paths[%d] %s\n", i, paths[i]);*/
			path = ft_concat_path(paths[i], command_args[0]);
			if (!access(path, F_OK | X_OK))
			{
				free(command_args[0]);
				command_args[0] = path;
				if (0 == pid)
				{
					/*printf("hna execute %s\n", command_args[0]);*/
					execve(command_args[0], command_args, ft_prep_envp(my_envp));
					/*printf("ta 9lwa ma trunut\n");*/
				}
				else if ((0 != pid) && to_wait)
				{
					/*int	status;*/
					/*int	res;*/

					wait_child(pid);
					/*waitpid(pid, &status, 0);*/
					/*if (WIFEXITED(status))*/
					/*	res = WEXITSTATUS(status);*/
					/*if (WIFSIGNALED(status))*/
					/*	res = WTERMSIG(status);*/
					/*printf("the exit status : %d\n", res);*/
				}
			}
			i++;
		}
		if (0 == pid)
			exit(1);
	}
}
