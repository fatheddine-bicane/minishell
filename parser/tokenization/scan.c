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

t_token	*token_end(t_token *head, t_token *tail)
{
	if (head == NULL)
		head = token_new(T_EOF, "");
	else
	{
		tail->next = token_new(T_EOF, "");
		if (tail->next == NULL)
			return (tokens_free(head), NULL);
		tail->next->prev = tail;
	}
	return (head);
}

bool	token_head(t_token **phead, char *src, size_t *current, char **err_msg)
{
	t_token	*head;

	head = token_identify(src, current, err_msg);
	if (head == NULL)
		return (false);
	if (head->type == T_SKIPPABLE)
	{
		token_free(head);
		head = NULL;
		return (true);
	}
	*phead = head;
	return (true);
}

bool	token_tail(t_token **ptail, char *src, size_t *current, char **err_msg)
{
	t_token	*tail;
	t_token	*tmp;

	if (ptail == NULL || *ptail == NULL)
		return (false);
	tail = *ptail;
	tail->next = token_identify(src, current, err_msg);
	if (tail->next == NULL)
		return (false);
	if (tail->next->type == T_SKIPPABLE)
	{
		token_free(tail->next);
		tail->next = NULL;
		return (true);
	}
	tmp = tail;
	*ptail = tail->next;
	tail->next->prev = tmp;
	return (true);
}

t_token	*tokens_scan(char *src, char **err_msg)
{
	size_t	current;
	t_token	*head;
	t_token	*tail;

	head = NULL;
	tail = NULL;
	current = 0;
	while (src[current])
	{
		if (head == NULL)
		{
			if (!token_head(&head, src, &current, err_msg))
				return (NULL);
			tail = head;
		}
		else
		{
			if (!token_tail(&tail, src, &current, err_msg))
				return (token_free(head), NULL);
		}
	}
	return (token_end(head, tail));
}
