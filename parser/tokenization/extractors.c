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
	start = *current - 1;
	if (single)
	{
		quote = '\'';
		type = T_STR_SINGLE;
	}
	while (src[*current] && src[*current] != quote)
		*current += 1;
	if (!src[*current])
		return (sn_eprintf("unexpected EOF while looking for matching `%c`\n",
				quote), NULL);
	*current += 1;
	substr = sn_substr(src, start, *current - start);
	return (token_new(type, substr));
}

static t_quote_state	init_quote_state(void)
{
	static t_quote_state	state;

	state.is_quoted = false;
	state.quote_start = '\0';
	state.quote_end = '\0';
	return (state);
}

static void	quote_state_quote(t_quote_state *state, char target)
{
	if (state->is_quoted)
		state->quote_end = target;
	else
		state->quote_start = target;
	if (state->quote_start == state->quote_end)
		state->is_quoted = !state->is_quoted;
	else
		state->is_quoted = true;
}

char	*extract_word(char *src, size_t *current)
{
	size_t	start;

	start = *current - 1;
	if (match_word(src, current, false))
	{
		while (match_word(src, current, false))
			continue ;
	}
	return (sn_substr(src, start, *current - start));
}

char	*extract_quoted_word(char *src, size_t *current)
{
	size_t			start;
	t_quote_state	state;

	start = *current - 1;
	state = init_quote_state();
	if (is_quote(src, start))
	{
		state.quote_start = src[start];
		state.is_quoted = true;
	}
	while (match_word(src, current, state.is_quoted))
	{
		if (is_quote(src, (*current) - 1))
			quote_state_quote(&state, src[(*current) - 1]);
	}
	if (state.is_quoted)
		return (sn_eprintf("unexpected EOF while looking for matching `%c`\n",
				state.quote_start), NULL);
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

	*current -= 1;
	if (match_char(src, current, '?'))
		return (token_new(T_VAR, sn_strdup("$?")));
	start = *current - 1;
	if (is_name(src, *current))
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
