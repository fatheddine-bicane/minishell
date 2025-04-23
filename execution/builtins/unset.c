/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:55:55 by fbicane           #+#    #+#             */
/*   Updated: 2025/04/23 09:46:51 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

int	ft_strncmp_(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	if (!s1 && !s2)
		return (0);
	i = 0;
	while ((s1[i] != 0 || s2[i] != 0 || s1[i] != '=') && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int	ft_find_variable(char **envp, char *variable)
{
	int	i;
	int	len;

	len = ft_strlen(variable);
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp_(envp[i], variable, len))
			return (i);
		i++;
	}
	return (-1);
}

/*static void	ft_free(char **arr_s)*/
/*{*/
/*	int	i;*/
/**/
/*	i = 0;*/
/*	if (!arr_s)*/
/*		return ;*/
/*	while (arr_s[i])*/
/*	{*/
/*		free(arr_s[i]);*/
/*		i++;*/
/*	}*/
/*	free (arr_s);*/
/*}*/

bool	ft_find_var(t_list *my_envp, char *variable)
{
	int	i;
	char *env_ptr;

	/*printf("not here\n");*/
	while (my_envp)
	{
		i = 0;
		env_ptr = (char *)my_envp->content;
		while (env_ptr[i] != '=' && env_ptr[i])
			i++;
		char	str[i];
		i = 0;
		while (env_ptr[i] != '=' && env_ptr[i])
		{
			str[i] = env_ptr[i];
			i++;
		}
		str[i] = '\0';
		if (!ft_strncmp(str, variable, ft_strlen(variable)))
			return (true);
		my_envp = my_envp->next;
	}
	return (false);
}

void	ft_unset(t_list **my_envp, char *variable)
{
	t_list	*env_to_del;
	t_list	*tmp_envp = (*my_envp);

	if (NULL == variable)
		return;

	char	*env_cont = (char *)(*my_envp)->content;
	int	i = 0;

	while (env_cont[i] && env_cont[i] != '=')
		i++;

	if (!ft_strncmp(env_cont, variable, i))
	{
		env_to_del = (*my_envp);
		(*my_envp) = (*my_envp)->next;
		(void)env_to_del;
		/*free(env_to_del->content);*/
		free(env_to_del);
		return ;
	}

	while (tmp_envp)
	{
		if (NULL == tmp_envp->next)
			return;

		env_cont = (char *)tmp_envp->next->content;
		i = 0;

		while (env_cont[i] && env_cont[i] != '=')
			i++;

		if (!ft_strncmp(env_cont, variable, i))
		{
			env_to_del = tmp_envp->next;
			tmp_envp->next = tmp_envp->next->next;
			(void)env_to_del;
			/*free(env_to_del->content);*/
			free(env_to_del);
			return ;
		}

		tmp_envp = tmp_envp->next;
	}
}
