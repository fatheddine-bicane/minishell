/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/10/25 22:21:05 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

t_cmd	*parse_cmd(t_token **token, int *status);

static t_cmd	*parse_pipe(t_token **token, int *status)
{
	t_cmd	*cmd;
	t_cmd	*left;
	t_cmd	*right;

	left = parse_cmd(token, status);
	if (left == NULL)
		return (NULL);
	while (match_token(token, 1, T_PIPE))
	{
		right = parse_cmd(token, status);
		if (right == NULL)
			return (ast_free(left), NULL);
		cmd = cmd_pipe_init(left, right, NULL);
		if (cmd == NULL)
			return (ast_free(left), ast_free(right), NULL);
		if (cmd != left)
		{
			left->parent = cmd;
			right->parent = cmd;
		}
		left = cmd;
	}
	return (left);
}

t_cmd	*parse_program(t_token **token, int *status)
{
	if (token == NULL || *token == NULL)
		return (NULL);
	if ((*token)->type == T_EOF)
		return (NULL);
	return (parse_pipe(token, status));
}
