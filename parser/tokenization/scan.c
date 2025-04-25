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

bool	match(char *src, size_t *current, char expected)
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

char	skip_space(char *src, size_t *current)
{
	char	c;

	c = src[(*current)++];
	while (c == ' ' || c == '\r' || c == '\t')
		c = src[(*current)++];
	if (!src[*current - 1])
		*current -= 1;
	return (c);
}

t_token	*scan_token(char *src, size_t *current)
{
	char	c;

	c = skip_space(src, current);
	if (c == '\n' || c == '\0')
		return (token_new(T_SKIPPABLE, ""));
	if (c == '(')
		return (token_new(T_LEFT_PAREN, "("));
	if (c == ')')
		return (token_new(T_RIGHT_PAREN, ")"));
	if (c == '*')
		return (token_new(T_WILDCARD, "*"));
	if (c == '=')
		return (token_new(T_EQUAL, "="));
	if (c == '&' && match(src, current, '&'))
		return (token_new(T_AND, "&&"));
	if (c == '|')
	{
		if (match(src, current, '|'))
			return (token_new(T_OR, "||"));
		return (token_new(T_PIPE, "|"));
	}
	if (c == '>')
	{
		if (match(src, current, '>'))
			return (token_new(T_REDIRECT_OUT_APPEND, ">>"));
		return (token_new(T_REDIRECT_OUT, ">"));
	}
	if (c == '<')
	{
		if (match(src, current, '<'))
			return (token_new(T_HEREDOC, "<<"));
		return (token_new(T_REDIRECT_IN, "<"));
	}
	return (token_new(T_UNKNOWN, sn_strndup(&src[*current - 1], 1)));
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
			head = scan_token(src, &current);
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
			last->next = scan_token(src, &current);
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
		head = token_new(T_EOF, NULL);
	else
	{
		last->next = token_new(T_EOF, NULL);
		if (last->next == NULL)
			return (tokens_free(head), NULL);
		last->next->prev = last;
	}
	return (head);
}
