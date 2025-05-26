/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/10/25 22:21:05 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

bool	is_name(char *src, size_t current)
{
	return (sn_isalpha(src[current]) || src[current] == '_');
}

bool	is_metachar(char *src, size_t current)
{
	if (!src[current])
		return (false);
	if (src[current] == '\'' || src[current] == '"')
		return (true);
	if (src[current] == ' ' || src[current] == '\t' || src[current] == '\n')
		return (true);
	if (src[current] == '|' || src[current] == '&')
		return (true);
	if (src[current] == '(' || src[current] == ')')
		return (true);
	if (src[current] == '<' || src[current] == '>')
		return (true);
	return (false);
}

bool	is_end(t_token *token)
{
	if (token->type == T_EOF)
		return (true);
	return (token->type == T_BLANK && token->next->type == T_EOF);
}

bool	is_redirect(t_token *token)
{
	return (token->type == T_REDIR_IN || token->type == T_REDIR_OUT
		|| token->type == T_REDIR_OUT_APPEND || token->type == T_HEREDOC);
}
