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
	if (type == T_STRING_SINGLE)
		return ("T_STRING_SINGLE");
	if (type == T_STRING_DOUBLE)
		return ("T_STRING_DOUBLE");
	if (type == T_PIPE)
		return ("T_PIPE");
	if (type == T_AND)
		return ("T_AND");
	if (type == T_OR)
		return ("T_OR");
	if (type == T_VAR)
		return ("T_VAR");
	if (type == T_VAR_STATUS)
		return ("T_VAR_STATUS");
	if (type == T_WILDCARD)
		return ("T_WILDCARD");
	if (type == T_SKIPPABLE)
		return ("T_SKIPPABLE");
	if (type == T_EOF)
		return ("T_EOF");
	if (type == T_UNKNOWN)
		return ("T_UNKNOWN");
	return (NULL);
}

const char	*token_type_str(t_token_type type)
{
	if (type == T_LEFT_PAREN)
		return ("T_LEFT_PAREN");
	if (type == T_RIGHT_PAREN)
		return ("T_RIGHT_PAREN");
	if (type == T_EQUAL)
		return ("T_EQUAL");
	if (type == T_REDIRECT_IN)
		return ("T_REDIRECT_IN");
	if (type == T_REDIRECT_OUT)
		return ("T_REDIRECT_OUT");
	if (type == T_REDIRECT_OUT_APPEND)
		return ("T_REDIRECT_OUT_APPEND");
	if (type == T_HEREDOC)
		return ("T_HEREDOC");
	if (type == T_HEREDOC_DELIMITER)
		return ("T_HEREDOC_DELIMITER");
	return (token_type_str2(type));
}
