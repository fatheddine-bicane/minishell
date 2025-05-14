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
	if (is_name(src, *current))
		found = true;
	if (found)
		*current += 1;
	return (found);
}

bool	match_token(t_token **head, size_t count, ...)
{
	t_token			*current;
	va_list			args;
	t_token_type	type;

	if (head == NULL || *head == NULL)
		return (false);
	current = *head;
	if (current->type == T_EOF)
		return (va_end(args), false);
	va_start(args, count);
	while (count--)
	{
		type = va_arg(args, int);
		if (current->type == type)
		{
			*head = current->next;
			return (va_end(args), true);
		}
	}
	return (va_end(args), false);
}

bool	match_tokens(t_token **head, size_t count, ...)
{
	t_token			*current;
	va_list			args;
	t_token_type	type;
	bool			matches;

	if (head == NULL || *head == NULL)
		return (false);
	current = *head;
	if (current->type == T_EOF)
		return (va_end(args), false);
	matches = true;
	va_start(args, count);
	while (count--)
	{
		type = va_arg(args, int);
		if (current->type != type)
		{
			matches = false;
			break ;
		}
		current = current->next;
	}
	if (matches)
		*head = current;
	return (va_end(args), matches);
}
