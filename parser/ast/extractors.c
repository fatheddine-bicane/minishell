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

int	extract_cmp_op(t_token *token)
{
	int	op;

	op = T_EOF;
	if (token->type == T_AND)
		op = T_AND;
	if (token->type == T_OR)
		op = T_OR;
	if (op == T_EOF)
	{
		sn_eprintf("token has unknown cmp type %s", token->str);
		exit(EXIT_FAILURE);
	}
	return (op);
}

char	*extract_lexeme_err(t_token *token)
{
	char	*lexeme;

	lexeme = token->lexeme;
	if (is_end(token))
		lexeme = "newline";
	if (token->type == T_BLANK && token->next->type != T_EOF)
		lexeme = token->next->lexeme;
	return (lexeme);
}

int	extract_redirect_type(t_token **token)
{
	t_token	*t;

	t = *token;
	while (!is_redirect(t))
		t = t->prev;
	return (t->type);
}

char	*extract_filename(t_token **token)
{
	t_str_builder	*sb;
	t_token			*t;

	sb = sb_create(10);
	if (sb == NULL)
		return (NULL);
	t = (*token)->prev;
	while (t->type != T_EOF && t->type != T_BLANK)
	{
		if (!sb_append_str(sb, t->lexeme, 0))
			return (sb_free(sb), NULL);
		t = t->next;
	}
	*token = t;
	return (sb_build_str(sb));
}
