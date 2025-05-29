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

/*typedef struct s_envp*/
/*{*/
/*	char			*variable_name;*/
/*	char			*variable_value;*/
/*	struct s_envp	*next;*/
/*	struct s_envp	*previous;*/
/*}	t_envp;*/
/**/
/*t_envp	*new_vaiable(char *var_name, char *var_value)*/
/*{*/
/*	t_envp	*new_var;*/
/**/
/*	new_var = malloc(sizeof(t_envp));*/
/*	if (!new_var)*/
/*		return (NULL);*/
/*	new_var->variable_name = ft_strdup(var_name);*/
/*	new_var->variable_value = ft_strdup(var_value);*/
/*	new_var->next = NULL;*/
/*	new_var->previous = NULL;*/
/*	return (new_var);*/
/*}*/
/**/
/*void	add_variable(t_envp **my_envp, t_envp *new_var)*/
/*{*/
/*	t_envp	*last_var;*/
/**/
/*	last_var = (*my_envp);*/
/*	if (!(*my_envp))*/
/*	{*/
/*		(*my_envp) = new_var;*/
/*		return ;*/
/*	}*/
/*	while (last_var->next)*/
/*		last_var = last_var->next;*/
/*	last_var->next = new_var;*/
/*	new_var->previous = last_var;*/
/*}*/
/**/
/*char	*get_name(char *var)*/
/*{*/
/*	int	i;*/
/*	char	*name;*/
/**/
/*	i = 0;*/
/*	while('=' != var[i] && var[i])*/
/*		i++;*/
/*	name = malloc(i);*/
/*	if (!name)*/
/*		return (NULL);*/
/*	i = 0;*/
/**/
/*	while('=' != var[i] && var[i])*/
/*	{*/
/*		name[i] = var[i];*/
/*		i++;*/
/*	}*/
/*	name[i] = '\0';*/
/*	return (name);*/
/*}*/
/**/
/*t_envp	*set_envp(char **envp)*/
/*{*/
/*	t_envp	*my_envp;*/
/*	int		i;*/
/**/
/*	my_envp = NULL;*/
/*	i = 0;*/
/*	while (envp[i])*/
/*	{*/
/*		if (!ft_strncmp(envp[i], "OLDPWD=", 7))*/
/*		{*/
/*			i++;*/
/*			continue ;*/
/*		}*/
/*		add_variable(&my_envp, new_vaiable(get_name(envp[i]), ft_strdup(ft_strchr(envp[i], '='))));*/
/*		i++;*/
/*	}*/
/*	return (my_envp);*/
/*}*/

void	envp_is_empty(t_list **my_envp)
{
	char	pwd[PATH_MAX];

	if (getcwd(pwd, PATH_MAX))
		ft_lstadd_back(my_envp, ft_lstnew(ft_strjoin("PWD=", pwd)));
	else
	{
		// TODO: error mssg
	}
	ft_lstadd_back(my_envp, ft_lstnew(ft_strdup("SHLVL=1")));
}

//INFO: this functions set a custum envp in alinked list so it can be modified later
t_list *ft_set_env(char **envp)
{
	t_list	*my_envp = NULL;
	int		i;

	if (!(*envp))
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
		if (!ft_strncmp(envp[i], "SHLVL=", 6))
		{
			int lvl = ft_atoi(envp[i] + 6);
			char (*shlvl_var) = ft_itoa(lvl + 1);
			printf("lvl = %d, %s, %s\n", lvl, envp[i] + 6, shlvl_var);
			ft_lstadd_back(&my_envp, ft_lstnew(ft_strjoin("SHLVL=", shlvl_var)));
			free(shlvl_var);
			i++;
			continue ;
			// BUG: the shlvl variable does not update when runing ./minishel (subshell)
		}
		ft_lstadd_back(&my_envp, ft_lstnew(ft_strdup((char *)envp[i])));
		i++;
	}
	return (my_envp);
}
