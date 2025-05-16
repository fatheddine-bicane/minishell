/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/10/25 22:21:05 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

char	*token_str_create(t_token *t)
{
	char	*str;
	char	*type;
	int		bytes;

	str = NULL;
	type = (char *)token_type_str(t->type);
	if (!t->lexeme)
		return (type);
	bytes = sn_sprintf(&str, "%s %s", type, t->lexeme);
	if (bytes == -1)
		return (type);
	return (str);
}

t_token	*token_new(t_token_type type, char *lexeme)
{
	t_token	*token;

	if (lexeme == NULL)
		return (NULL);
	token = malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->type = type;
	token->lexeme = lexeme;
	token->str = token_str_create(token);
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

void	token_free(t_token *t)
{
	t_token_type	type;

	if (t == NULL)
		return ;
	type = t->type;
	if (t->lexeme)
		free(t->str);
	if (type == T_STR_SINGLE || type == T_STR_DOUBLE)
		free(t->lexeme);
	if (type == T_WORD || type == T_VAR)
		free(t->lexeme);
	free(t);
}

void	tokens_free(t_token *token)
{
	t_token	*tmp;

	if (token == NULL)
		return ;
	while (token)
	{
		tmp = token->next;
		token_free(token);
		token = tmp;
	}
}

void	token_str(t_token *t, bool nl, bool all)
{
	while (t)
	{
		if (nl)
			sn_printf("%s\n", t->str);
		else
			sn_printf("%s", t->str);
		if (all)
			t = t->next;
		else
			break ;
	}
}
