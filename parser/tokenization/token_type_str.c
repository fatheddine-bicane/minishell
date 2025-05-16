/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/10/25 22:21:05 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

static const char	*token_type_str2(t_token_type type)
{
	if (type == T_STR_SINGLE)
		return ("T_STR_SINGLE");
	if (type == T_STR_DOUBLE)
		return ("T_STR_DOUBLE");
	if (type == T_PIPE)
		return ("T_PIPE");
	if (type == T_AND)
		return ("T_AND");
	if (type == T_OR)
		return ("T_OR");
	if (type == T_WILDCARD)
		return ("T_WILDCARD");
	if (type == T_SKIPPABLE)
		return ("T_SKIPPABLE");
	if (type == T_EOF)
		return ("T_EOF");
	return (NULL);
}

const char	*token_type_str(t_token_type type)
{
	if (type == T_LEFT_PAREN)
		return ("T_LEFT_PAREN");
	if (type == T_RIGHT_PAREN)
		return ("T_RIGHT_PAREN");
	if (type == T_REDIR_IN)
		return ("T_REDIRECT_IN");
	if (type == T_REDIR_OUT)
		return ("T_REDIRECT_OUT");
	if (type == T_REDIR_OUT_APPEND)
		return ("T_REDIRECT_OUT_APPEND");
	if (type == T_HEREDOC)
		return ("T_HEREDOC");
	if (type == T_BLANK)
		return ("T_BLANK");
	if (type == T_WORD)
		return ("T_WORD");
	if (type == T_VAR)
		return ("T_VAR");
	return (token_type_str2(type));
}
