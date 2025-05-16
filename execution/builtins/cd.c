/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 18:45:52 by fbicane           #+#    #+#             */
/*   Updated: 2025/04/06 19:08:18 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

char	*ft_home_path(t_list *my_envp)
{
	while (my_envp)
	{
		if (!ft_strncmp(my_envp->content, "HOME=", 5))
			return (ft_strdup(my_envp->content + 5));
		my_envp = my_envp->next;
	}
	return (NULL);
}

void	ft_change_oldpwd(t_list **my_envp, char *oldpwd)
{
	t_list	*tmp;

	tmp = (*my_envp);
	while (tmp)
	{
		if (!ft_strncmp(tmp->content, "OLDPWD=", 7))
		{
			free(tmp->content);
			tmp->content = oldpwd;
			return;
		}
		tmp = tmp->next;
	}
	if (NULL == tmp)
		ft_lstadd_back(my_envp, ft_lstnew(oldpwd));
}

char	*ft_set_oldpwd(void)
{
	char	oldpwd[PATH_MAX];

	if (getcwd(oldpwd, sizeof(oldpwd)))
	{
		return (ft_strjoin("OLDPWD=", oldpwd));
	}
	else
	{
		perror("getcwd() error");
		// TODO: exit
	}
	return (NULL);

}

void	ft_cd(char *path, t_list **my_envp)
{
	char	*home_path;
	char	*oldpwd;

	home_path = ft_home_path(*my_envp);
	oldpwd = ft_set_oldpwd();
	if (!path)
	{
		if (!home_path)
		{
			perror("minishell: cd: HOME not set\n");
			free(home_path);
			free(oldpwd);
			return ;
		}
		if (-1 == chdir(home_path))
		{
			perror("minishell: chdir() error\n");
			free(home_path);
			free(oldpwd);
			return ;
		}
		ft_change_oldpwd(my_envp, oldpwd);
	}
	else
	{
		if (-1 == chdir(path))
		{
			perror("minishell: cd: ");
			perror(path);
			perror(": No such file or directory\n");
			free(home_path);
			free(oldpwd);
			return;
		}
		ft_change_oldpwd(my_envp, oldpwd);
	}
}
