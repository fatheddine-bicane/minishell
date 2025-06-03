/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansoin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/10/25 22:21:05 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

char	*param_expand(char *src)
{
	t_str_builder	*sb;
	t_token			*token;
	t_token			*head;
	size_t			len;
	size_t			i;
	size_t			start;
	size_t			offset;

	token = tokens_scan(src);
	if (token == NULL)
		return (free(src), NULL);
	head = token;
	sb = sb_create(10);
	if (sb == NULL)
		return (tokens_free(head), free(src), NULL);
	token_str(head, false, true);
	while (token && token->type != T_EOF)
	{
		len = sn_strlen(token->lexeme);
		if (token->type == T_STR_SINGLE)
		{
			if (len == 2 && !sb_append_char(sb, '\0'))
				return (tokens_free(head), sb_free(sb), free(src), NULL);
			if (len > 2 && !sb_append_str(sb, token->lexeme + 1, len - 2))
				return (tokens_free(head), sb_free(sb), free(src), NULL);
		}
		else if (token->type == T_VAR)
		{
			// TODO(karim): expand var
		}
		else if (token->type == T_STR_DOUBLE)
		{
			if (len == 2 && !sb_append_char(sb, '\0'))
				return (tokens_free(head), sb_free(sb), free(src), NULL);
			i = 1;
			start = 1;
			offset = 0;
			while (token->lexeme[i])
			{
				if (token->lexeme[i] == '$' && is_name(token->lexeme, i + 1))
				{
					if (i > start && !sb_append_str(sb, token->lexeme + start, i - start))
						return (tokens_free(head), sb_free(sb), free(src), NULL);
					offset = i + 1;
					i += 1;
					while (is_name(token->lexeme, i))
						i++;
					if (!sb_append_str(sb, token->lexeme + offset, i - offset))
						return (tokens_free(head), sb_free(sb), free(src), NULL);
					printf("substr = %s\n", sb->buff[sb_len(sb) - 1]);
					offset = 0;
					start = i;
					continue ;
				}
				i++;
			}
			if (i > start && !sb_append_str(sb, token->lexeme + start, i - start - 1))
				return (tokens_free(head), sb_free(sb), free(src), NULL);
		}
		else
		{
			if (!sb_append_str(sb, token->lexeme, len))
				return (tokens_free(head), sb_free(sb), free(src), NULL);
		}
		token = token->next;
	}
	return (free(src), tokens_free(head), sb_build_str(sb));
}

bool	expand_params(char **args)
{
	size_t	i;

	if (args == NULL)
		return (false);
	i = 0;
	while (args[i] != NULL)
	{
		args[i] = param_expand(args[i]);
		sn_printf("expanded into (%s)\n", args[i]);
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

char	*param_expand2(char *src)
{
	size_t			i;
	size_t			offset;
	size_t			start;
	t_str_builder	*sb;

	i = 0;
	if (!src[i])
		return (src);
	sb = sb_create(10);
	start = 0;
	while (src[i])
	{
		if (src[i] == '$' && is_name(src, i + 1))
		{
			if (i > start)
				sb_append_str(sb, src + start, i - start);
			offset = i + 1;
			i += 1;
			while (is_name(src, i))
				i++;
			sb_append_str(sb, src + offset, i - offset);
			printf("substr = %s\n", sb->buff[sb_len(sb) - 1]);
			offset = 0;
			start = i;
			continue ;
		}
		i++;
	}
	if (i > start)
		sb_append_str(sb, src + start, i - start);
	free(src);
	return (sb_build_str(sb));
}
