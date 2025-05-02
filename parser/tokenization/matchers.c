/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matchers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/10/25 22:21:05 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

bool	match_char(char *src, size_t *current, char expected)
{
	if (!src[*current])
		return (false);
	if (src[*current] == expected)
	{
		*current += 1;
		return (true);
	}
	return (false);
}

bool	is_metachar(char *src, size_t current)
{
	if (!src[current])
		return (false);
	if (src[current] == '\'' || src[current] == '"')
		return (true);
	if (src[current] == ' ' || src[current] == '\t')
		return (true);
	if (src[current] == '|' || src[current] == '&')
		return (true);
	if (src[current] == '(' || src[current] == ')')
		return (true);
	if (src[current] == '<' || src[current] == '>')
		return (true);
	return (false);
}

bool	match_word(char *src, size_t *current)
{
	if (!src[*current])
		return (false);
	if (is_metachar(src, *current))
		return (false);
	*current += 1;
	return (true);
}

bool	match_var(char *src, size_t *current)
{
	bool	found;

	found = false;
	if (src[*current] == '?')
		found = true;
	if (sn_isalpha(src[*current]) || src[*current] == '_')
		found = true;
	if (found)
		*current += 1;
	return (found);
}

bool	match_identifier(char *src, size_t *current)
{
	size_t	start;
	bool	found;

	found = false;
	start = *current - 1;
	if (!sn_isalpha(src[*current]) && src[*current] != '_')
		return (found);
	while (sn_isalphanum(src[*current]) || src[*current] == '_')
		*current += 1;
	if (start >= 1 && src[start - 1] == '=')
		found = true;
	if (start >= 2 && src[start - 2] == '+' && src[start - 1] == '=')
		found = true;
	if (match_char(src, current, '='))
		found = true;
	if (match_char(src, current, '+') && match_char(src, current, '='))
		found = true;
	*current = start + 1;
	return (found);
}
