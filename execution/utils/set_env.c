/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:48:49 by fbicane           #+#    #+#             */
/*   Updated: 2025/06/16 16:06:58 by fbicane          ###   ########.fr       */
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

static void	ft_set_env_utils(t_set_envp *s_envp, char **envp)
{
	s_envp->lvl = ft_atoi(envp[s_envp->i] + 6);
	s_envp->shlvl_var = ft_itoa(s_envp->lvl + 1);
	ft_lstadd_back(&s_envp->my_envp,
		ft_lstnew(ft_strjoin("SHLVL=", s_envp->shlvl_var)));
	free(s_envp->shlvl_var);
	s_envp->i++;
}

//INFO: set custum envp (list)
t_list	*ft_set_env(char **envp)
{
	t_set_envp	s_envp;

	s_envp.my_envp = NULL;
	if (NULL == (*envp))
		return (envp_is_empty(&s_envp.my_envp), s_envp.my_envp);
	s_envp.i = 0;
	while (envp[s_envp.i])
	{
		if (!ft_strncmp(envp[s_envp.i], "OLDPWD=", 7))
		{
			s_envp.i++;
			continue ;
		}
		else if (!ft_strncmp(envp[s_envp.i], "SHLVL=", 6))
		{
			ft_set_env_utils(&s_envp, envp);
			continue ;
		}
		else if (!ft_strncmp(envp[s_envp.i], "_=", 2) && ++s_envp.i)
			continue ;
		ft_lstadd_back(&s_envp.my_envp, ft_lstnew(ft_strdup((envp[s_envp.i]))));
		s_envp.i++;
	}
	return (s_envp.my_envp);
}
