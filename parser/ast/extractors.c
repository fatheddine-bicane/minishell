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

t_cmp_type	extract_cmp_op(t_token *token)
{
	t_cmp_type	op;

	op = OP_UNKNOWN;
	if (token->type == T_AND)
		op = OP_AND;
	if (token->type == T_OR)
		op = OP_OR;
	if (op == OP_UNKNOWN)
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
	if (token->type == T_EOF)
		lexeme = "newline";
	if (token->type == T_BLANK && token->next->type == T_EOF)
		lexeme = "newline";
	if (token->type == T_BLANK && token->next->type != T_EOF)
		lexeme = token->next->lexeme;
	return (lexeme);
}
