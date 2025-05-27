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

t_token	*extract_str(char *src, size_t *current, bool single)
{
	size_t			start;
	char			*substr;
	char			quote;
	t_token_type	type;

	quote = '"';
	type = T_STR_DOUBLE;
	if (single)
	{
		quote = '\'';
		type = T_STR_SINGLE;
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
	size_t	start;

	start = *current - 1;
	if (match_word(src, current))
	{
		while (match_word(src, current))
			continue ;
	}
	return (sn_substr(src, start, *current - start));
}

t_token	*extract_identifier(char *src, size_t *current)
{
	size_t	start;
	char	*substr;

	start = *current - 1;
	while (is_name(src, *current))
		*current += 1;
	substr = sn_substr(src, start, *current - start);
	if (substr == NULL)
		return (NULL);
	return (token_new(T_WORD, substr));
}

t_token	*extract_var(char *src, size_t *current)
{
	size_t	start;
	char	*substr;

	if (match_char(src, current, '?'))
		return (token_new(T_VAR, sn_strdup("?")));
	start = *current - 1;
	if (is_name(src, *current - 1))
	{
		while (is_name(src, *current) || sn_isalphanum(src[*current]))
			*current += 1;
	}
	substr = sn_substr(src, start, *current - start);
	if (substr == NULL)
		return (NULL);
	return (token_new(T_VAR, substr));
}

t_token	*extract_blank(char *src, size_t *current)
{
	while (src[*current] && (src[*current] == ' ' || src[*current] == '\t'))
		*current += 1;
	return (token_new(T_BLANK, " "));
}
