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

bool	match_word(char *src, size_t *current, bool is_quoted)
{
	if (!src[*current])
		return (false);
	if (is_metachar(src, *current, is_quoted))
		return (false);
	*current += 1;
	return (true);
}

bool	match_word_bonus(char *src, size_t *current, bool is_quoted)
{
	if (!src[*current])
		return (false);
	if (is_metachar_bonus(src, *current, is_quoted))
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
	size_t			i;

	if (head == NULL || *head == NULL || (*head)->type == T_EOF)
		return (false);
	current = *head;
	va_start(args, count);
	i = 0;
	while (i++ < count)
	{
		type = (t_token_type)va_arg(args, int);
		if (current->type == T_BLANK && type != T_BLANK)
			current = current->next;
		if (current->type == type)
		{
			*head = current->next;
			return (va_end(args), true);
		}
	}
	return (va_end(args), false);
}
