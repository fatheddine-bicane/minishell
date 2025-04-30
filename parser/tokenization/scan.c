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

t_token	*extract_id_cmd_val(char *src, size_t *current, bool isval)
{
	char	*substr;
	size_t	start;

	start = *current - 1;
	while (src[*current] == '_' || sn_isalphanum(src[*current]))
		*current += 1;
	substr = sn_substr(src, start, *current - start);
	if (substr == NULL)
		return (NULL);
	if (isval)
		return ((*current += 1), token_new(T_VAR_VALUE, substr));
	if (src[*current] == '=')
		return (token_new(T_IDENTIFIER, substr));
	return (token_new(T_CMD, substr));
}

t_token	*extract_var(char *src, size_t *current)
{
	char	*substr;
	size_t	start;

	start = *current - 1;
	while (src[*current] == '_' || sn_isalphanum(src[*current]))
		*current += 1;
	substr = sn_substr(src, start, *current - start);
	if (substr == NULL)
		return (NULL);
	return (token_new(T_VAR, substr));
}

t_token	*scan_token(char *src, size_t *current)
{
	char	c;

	c = src[(*current)++];
	if (c == '\n' || c == '\0' || c == ' ' || c == '\r' || c == '\t')
		return (token_new(T_SKIPPABLE, ""));
	if (c == '(')
		return (token_new(T_LEFT_PAREN, "("));
	if (c == ')')
		return (token_new(T_RIGHT_PAREN, ")"));
	if (c == '*')
		return (token_new(T_WILDCARD, "*"));
	if (c == '+' && match(src, current, '='))
		return (token_new(T_APPEND, "+="));
	if (c == '=')
	{
		if (src[*current] == '_' || sn_isalphanum(src[*current]))
			return ((*current += 1), extract_id_cmd_val(src, current, true));
		return (token_new(T_EQUAL, "="));
	}
	if (c == '$')
	{
		if (match(src, current, '?'))
			return (token_new(T_VAR_STATUS, "$?"));
		if (src[*current] == '_' || sn_isalphanum(src[*current]))
			return ((*current += 1), extract_var(src, current));
	}
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
	if (c == '\'' || c == '"')
		return (extract_str(src, current, c == '\''));
	if (sn_isalpha(c) || c == '_')
		return (extract_id_cmd_val(src, current, false));
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
