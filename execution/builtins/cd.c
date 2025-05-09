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

/*void	ft_change_pwd(t_list **my_envp)*/
/*{*/
/*	char	**pwd_to_del;*/
/**/
/*	pwd_to_del = malloc(sizeof(char *) * 2);*/
/*	if (!pwd_to_del)*/
/*	{*/
/*		// TODO: error mssg*/
/*	}*/
/*	pwd_to_del[0] = ft_strdup("PWD");*/
/*	pwd_to_del[1] = ft_strdup("");*/
/*	ft_unset(my_envp, pwd_to_del);*/
/*	ft_export()*/
/*}*/

void	ft_cd(char *path, t_list **my_envp)
{
	char	*home_path;

	home_path = ft_home_path(*my_envp);
	if (!path)
	{
		if (!home_path)
		{
			perror("minishell: cd: HOME not set\n");
			return ;
		}
		if (-1 == chdir(home_path))
		{
			// TODO: error mssg and free()
		}
	}
	else
	{
		errno = chdir(path);
		if (errno == -1)
			errno = ENOENT;
		ft_pwd();
	}
}
