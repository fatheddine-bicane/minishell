/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/10/25 22:21:05 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

t_token	*token_identify_multi(char *src, size_t *current, char c)
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
			return (token_new(T_REDIRECT_OUT_APPEND, ">>"));
		return (token_new(T_REDIRECT_OUT, ">"));
	}
	if (c == '<')
	{
		if (match_char(src, current, '<'))
			return (token_new(T_HEREDOC, "<<"));
		return (token_new(T_REDIRECT_IN, "<"));
	}
	if (c == '$' && match_var(src, current))
		return (extract_var(src, current));
	return (token_new(T_WORD, extract_word(src, current)));
}

t_token	*token_identify(char *src, size_t *current)
{
	char	c;

	c = src[(*current)++];
	if (c == '\n' || c == '\0')
		return (token_new(T_SKIPPABLE, ""));
	if (c == ' ' || c == '\t')
		return (extract_blank(src, current));
	if (c == '\'' || c == '"')
		return (extract_str(src, current, c == '\''));
	if (c == '(')
		return (token_new(T_LEFT_PAREN, "("));
	if (c == ')')
		return (token_new(T_RIGHT_PAREN, ")"));
	if (c == '*')
		return (token_new(T_WILDCARD, "*"));
	if (c == '&' && match_char(src, current, '&'))
		return (token_new(T_AND, "&&"));
	return (token_identify_multi(src, current, c));
}

t_token	*tokens_scan(char *src)
{
	size_t	current;
	t_token	*head;
	t_token	*last;
	t_token	*tmp;

	current = 0;
	head = NULL;
	while (src[current])
	{
		if (head == NULL)
		{
			head = token_identify(src, &current);
			if (head == NULL)
				return (NULL);
			if (head->type == T_SKIPPABLE)
			{
				token_free(head);
				head = NULL;
				continue ;
			}
			last = head;
		}
		else
		{
			last->next = token_identify(src, &current);
			if (last->next == NULL)
				return (tokens_free(head), NULL);
			if (last->next->type == T_SKIPPABLE)
			{
				token_free(last->next);
				last->next = NULL;
				continue ;
			}
			tmp = last;
			last = last->next;
			last->prev = tmp;
		}
	}
	if (head == NULL)
		head = token_new(T_EOF, "");
	else
	{
		last->next = token_new(T_EOF, "");
		if (last->next == NULL)
			return (tokens_free(head), NULL);
		last->next->prev = last;
	}
	return (head);
}
