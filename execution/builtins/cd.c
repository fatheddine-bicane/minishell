/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 18:45:52 by fbicane           #+#    #+#             */
/*   Updated: 2025/05/31 16:35:12 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

char	*ft_home_path(t_list *my_envp)
{
	t_list *tmp;

	tmp = my_envp;
	while (tmp)
	{
		if (!ft_strncmp(tmp->content, "HOME=", 5))
			return (ft_strdup(tmp->content + 5));
		tmp = tmp->next;
	}
	return (NULL);
}

void	ft_change_oldpwd(t_shell *shell, char *oldpwd)
{
	t_list	*tmp;
	t_list	*my_envp;

	tmp = shell->my_envp;
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
	my_envp = shell->my_envp;
	if (NULL == tmp)
		ft_lstadd_back(&my_envp, ft_lstnew(oldpwd));
}

char	*ft_set_oldpwd(void)
{
	char	oldpwd[PATH_MAX];

	if (getcwd(oldpwd, sizeof(oldpwd)))
	{
		return (ft_strjoin("OLDPWD=", oldpwd));
	}
	else
		perror("getcwd()");
	return (NULL);
}

void	ft_cd(t_shell *shell)
{
	t_cd	cd;

	cd.home_path = ft_home_path(shell->my_envp);
	cd.oldpwd = ft_set_oldpwd();
	cd.shell = shell;
	if (!shell->cmd->u_as.exec.argv[1])
	{
		if (!cd.home_path)
			return (cd_error(&cd, 1));
		if (-1 == chdir(cd.home_path))
			return (cd_error(&cd, 2));
		ft_change_oldpwd(shell, cd.oldpwd);
		free(cd.home_path);
	}
	else
	{
		if (-1 == chdir(shell->cmd->u_as.exec.argv[1]))
			return (cd_error(&cd, 3));
		ft_change_oldpwd(shell, cd.oldpwd);
		free(cd.home_path);
	}
	shell->exit_status = 0;
}
