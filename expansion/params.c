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

bool	expand_var(t_shell *shell, t_str_builder *sb, char *variable,
			size_t len);

bool	parse_quote_param(t_shell *shell, t_str_builder *sb, char *str,
		size_t len)
{
	size_t	i;
	size_t	offset;

	i = 1;
	offset = 1;
	while (str[i] && i < len - 1)
	{
		if (str[i] == '$' && (str[i + 1] == '?' || is_name(str, i + 1)))
		{
			if (i > offset && !sb_append_str(sb, str + offset, i - offset))
				return (false);
			offset = i + 1;
			i += 2;
			while (is_name(str, i) && str[offset] != '?')
				i++;
			if (!expand_var(shell, sb, str + offset, i - offset))
				return (false);
			offset = i;
			continue ;
		}
		i++;
	}
	if (i > offset)
		return (sb_append_str(sb, str + offset, i - offset));
	return (true);
}

bool	parse_param(t_token *token, t_str_builder *sb, t_shell *shell)
{
	size_t	len;

	len = sn_strlen(token->lexeme);
	if (token->type == T_STR_SINGLE)
	{
		if (len == 2)
			return (sb_append_char(sb, '\0'));
		return (sb_append_str(sb, token->lexeme + 1, len - 2));
	}
	if (token->type == T_VAR)
		return (expand_var(shell, sb, token->lexeme + 1, len - 1));
	if (token->type == T_STR_DOUBLE)
	{
		if (len == 2)
			return (sb_append_char(sb, '\0'));
		return (parse_quote_param(shell, sb, token->lexeme, len));
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

// NOTE(karim): // maybe reuse src if expansion fails
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
		free(src);
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
