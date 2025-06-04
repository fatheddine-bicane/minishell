/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/10/25 22:21:05 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

char	*ft_get_var_value(t_list *my_envp, char *variable, size_t len)
{
	char	*curr;
	char	*p;

	while (my_envp)
	{
		curr = (char *)my_envp->content;
		if (sn_strncmp(curr, variable, len) == 0)
		{
			p = sn_strchr(curr, '=');
			if (p != NULL && (size_t)(p - curr) == len)
				return (p + 1);
		}
		my_envp = my_envp->next;
	}
	return (NULL);
}

bool	expand_var(t_shell *shell, t_str_builder *sb, char *variable,
		size_t len)
{
	char	*var;

	if (variable[0] == '?')
		return (sb_append_nbr(sb, shell->exit_status));
	var = ft_get_var_value(shell->my_envp, variable, len);
	if (var == NULL)
		return (sb_append_char(sb, '\0'));
	return (sb_append_str(sb, var, 0));
}
