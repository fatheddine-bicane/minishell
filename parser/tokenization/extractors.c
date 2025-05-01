/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extractors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/10/25 22:21:05 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

static bool	consume_word(char *src, size_t *current)
{
	if (!src[*current])
		return (false);
	if (match_word(src, current))
	{
		while (src[*current] && match_word(src, current))
			continue ;
		return (true);
	}
	return (false);
}

t_token	*extract_str(char *src, size_t *current, bool single)
{
	size_t			start;
	char			*substr;
	char			quote;
	t_token_type	type;

	quote = '"';
	type = T_STRING_DOUBLE;
	if (single)
	{
		quote = '\'';
		type = T_STRING_SINGLE;
	}
	start = *current;
	while (src[*current] && src[*current] != quote)
		*current += 1;
	if (!src[*current])
		return (sn_printf_fd(STDERR_FILENO,
				"unexpected EOF while looking for matching `%c`\n", quote),
			NULL);
	substr = sn_substr(src, start, *current - start);
	if (substr == NULL)
		return (NULL);
	*current += 1;
	return (token_new(type, substr));
}

char	*extract_word(char *src, size_t *current)
{
	char	*substr;
	size_t	start;

	start = *current - 1;
	consume_word(src, current);
	substr = sn_substr(src, start, *current - start);
	if (substr == NULL)
		return (NULL);
	return (substr);
}

t_token	*extract_identifier(char *src, size_t *current)
{
	size_t	start;
	char	*substr;

	start = *current - 1;
	while (sn_isalphanum(src[*current]) || src[*current] == '_')
		*current += 1;
	substr = sn_substr(src, start, *current - start);
	if (substr == NULL)
		return (NULL);
	return (token_new(T_IDENTIFIER, substr));
}
