/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_identify_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/10/25 22:21:05 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

char	*extract_word_bonus(char *src, size_t *current)
{
	size_t	start;

	start = *current - 1;
	if (match_word_bonus(src, current, false))
	{
		while (match_word_bonus(src, current, false))
			continue ;
	}
	return (sn_substr(src, start, *current - start));
}

static t_token	*token_identify_multi(char *src, size_t *current, char c)
{
	if (c == '|')
	{
		if (match_char(src, current, '|'))
			return (token_new(T_OR, "||"));
		return (token_new(T_PIPE, "|"));
	}
	if (c == '>')
	{
		if (match_char(src, current, '>'))
			return (token_new(T_REDIR_OUT_APPEND, ">>"));
		return (token_new(T_REDIR_OUT, ">"));
	}
	if (c == '<')
	{
		if (match_char(src, current, '<'))
			return (token_new(T_HEREDOC, "<<"));
		return (token_new(T_REDIR_IN, "<"));
	}
	if (c == '$' && match_var(src, current))
		return (extract_var(src, current));
	return (token_new(T_WORD, extract_word_bonus(src, current)));
}

t_token	*token_identify_bonus(char *src, size_t *current, char **err_msg)
{
	char	c;

	c = src[(*current)++];
	if (c == '\n' || c == '\0')
		return (token_new(T_SKIPPABLE, ""));
	if (c == ' ' || c == '\t')
		return (extract_blank(src, current));
	if (c == '\'' || c == '"')
		return (extract_str(src, current, c == '\'', err_msg));
	if (c == '(')
		return (token_new(T_LEFT_PAREN, "("));
	if (c == ')')
		return (token_new(T_RIGHT_PAREN, ")"));
	if (c == '&' && match_char(src, current, '&'))
		return (token_new(T_AND, "&&"));
	return (token_identify_multi(src, current, c));
}
