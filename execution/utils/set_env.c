/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:48:49 by fbicane           #+#    #+#             */
/*   Updated: 2025/05/29 13:59:41 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

void	envp_is_empty(t_list **my_envp)
{
	char	pwd[PATH_MAX];

	if (NULL == getcwd(pwd, PATH_MAX))
		perror("getcwd failed");
	ft_lstadd_back(my_envp, ft_lstnew(ft_strjoin("PWD=", pwd)));
	ft_lstadd_back(my_envp, ft_lstnew(ft_strdup("SHLVL=1")));
}

//INFO: this functions set a custum envp in alinked list so it can be modified later
t_list *ft_set_env(char **envp)
{
	t_list	*my_envp = NULL;
	int		i;
	char	*shlvl_var;
	int		lvl;

	if (NULL == (*envp))
	{
		envp_is_empty(&my_envp);
		return (my_envp);
	}

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "OLDPWD=", 7))
		{
			i++;
			continue ;
		}
		else if (!ft_strncmp(envp[i], "SHLVL=", 6))
		{
			lvl = ft_atoi(envp[i] + 6);
			shlvl_var = ft_itoa(lvl + 1);
			ft_lstadd_back(&my_envp, ft_lstnew(ft_strjoin("SHLVL=", shlvl_var)));
			free(shlvl_var);
			i++;
			continue ;
		}
		else if (!ft_strncmp(envp[i], "_=", 2))
		{
			i++;
			continue ;
		}
		ft_lstadd_back(&my_envp, ft_lstnew(ft_strdup((envp[i]))));
		i++;
	}
	return (my_envp);
}
