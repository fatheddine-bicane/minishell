/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/10/25 22:21:05 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

char	*ft_get_var_value(int len, char *variable, t_list *my_envp)
{
	while (my_envp)
	{
		if (!ft_strncmp(variable, (char *)my_envp->content, len))
			return (ft_strdup((char *)my_envp->content + len + 1));
		my_envp = my_envp->next;
	}
	return (NULL);
}

bool	parse_param(t_token *token, t_str_builder *sb, t_shell *shell)
{
	char	*var;
	size_t	len;
	size_t	i;
	size_t	start;
	size_t	offset;

	len = sn_strlen(token->lexeme);
	if (token->type == T_STR_SINGLE)
	{
		if (len == 2 && !sb_append_char(sb, '\0'))
			return (false);
		return (sb_append_str(sb, token->lexeme + 1, len - 2));
	}
	if (token->type == T_VAR)
	{
		if (token->lexeme[1] == '?')
			return (!sb_append_nbr(sb, shell->exit_status));
		var = ft_get_var_value(len - 1, token->lexeme + 1, shell->my_envp);
		if (var == NULL)
			return (sb_append_char(sb, '\0'));
		if (!sb_append_str(sb, var, 0))
			return (free(var), false);
		return (free(var), true);
	}
	if (token->type == T_STR_DOUBLE)
	{
		if (len == 2)
			return (false);
		i = 1;
		start = 1;
		offset = 0;
		while (token->lexeme[i] && i < len - 1)
		{
			if (token->lexeme[i] == '$' && token->lexeme[i + 1] == '?')
			{
				if (!sb_append_nbr(sb, shell->exit_status))
					return (false);
				i += 2;
				offset = 0;
				start = i;
				continue ;
			}
			if (token->lexeme[i] == '$' && is_name(token->lexeme, i + 1))
			{
				if (i > start && !sb_append_str(sb, token->lexeme + start, i - start))
					return (false);
				offset = i + 1;
				i += 1;
				while (is_name(token->lexeme, i))
					i++;
				var = ft_get_var_value(i - offset, token->lexeme + offset, shell->my_envp);
				if (var == NULL && !sb_append_char(sb, '\0'))
					return (false);
				if (var != NULL && !sb_append_str(sb, var, 0))
					return (free(var), false);
				free(var);
				offset = 0;
				start = i;
				continue ;
			}
			i++;
		}
		if (i > start && !sb_append_str(sb, token->lexeme + start, i - start))
			return (false);
		return (true);
	}
	return (sb_append_str(sb, token->lexeme, len));
}

char	*param_expand(char *src, t_shell *shell)
{
	t_str_builder	*sb;
	t_token			*token;
	t_token			*head;

	token = tokens_scan(src);
	if (token == NULL)
		return (NULL);
	head = token;
	sb = sb_create(10);
	if (sb == NULL)
		return (tokens_free(head), NULL);
	while (token && token->type != T_EOF)
	{
		if (!parse_param(token, sb, shell))
			return (tokens_free(head), sb_free(sb), NULL);
		token = token->next;
	}
	return (tokens_free(head), sb_build_str(sb));
}

bool	expand_params(char **args, t_shell *shell)
{
	size_t	i;
	char	*src;

	if (args == NULL)
		return (false);
	i = 0;
	while (args[i] != NULL)
	{
		src = args[i];
		args[i] = param_expand(src, shell);
		free(src); // maybe reuse src if expansion fails
		if (args[i] == NULL)
		{
			i++;
			while (args[i] != NULL)
			{
				free(args[i]);
				args[i++] = NULL;
			}
			return (false);
		}
		i++;
	}
	return (true);
}
