/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/10/25 22:21:05 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

t_cmd	*parse_program_bonus(t_token **token, int *status);
t_cmd	*parse_cmd(t_token **token, int *status);
t_cmd	*parse_redirect(t_token **token, int *status);
t_cmd	*append_redirect(t_cmd *root, t_cmd *new);

t_cmd	*parse_group(t_token **token, int *status)
{
	t_cmd	*cmd;
	t_cmd	*subshell;

	if (match_token(token, 1, T_LEFT_PAREN))
	{
		subshell = parse_program_bonus(token, status);
		if (subshell == NULL || *status == -1)
			return (NULL);
		cmd = cmd_group_init(subshell, NULL);
		if (cmd == NULL || *status == -1)
			return (ast_free(cmd), NULL);
		subshell->parent = cmd;
		if (!match_token(token, 1, T_RIGHT_PAREN))
			return ((*status = -1), ast_free(cmd), NULL);
		cmd = append_redirect(parse_redirect(token, status), cmd);
		if (*status == -1)
			return (ast_free(cmd), NULL);
		return (cmd);
	}
	return (parse_cmd(token, status));
}

t_cmd	*parse_pipe(t_token **token, int *status)
{
	t_cmd	*cmd;
	t_cmd	*left;
	t_cmd	*right;

	left = parse_group(token, status);
	if (left == NULL)
		return (NULL);
	while (match_token(token, 1, T_PIPE))
	{
		right = parse_group(token, status);
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

t_cmd	*parse_compound(t_token **token, int *status)
{
	t_cmd	*cmd;
	t_cmd	*left;
	t_cmd	*right;
	int		op;

	left = parse_pipe(token, status);
	if (left == NULL)
		return (NULL);
	while (match_token(token, 1, T_AND) || match_token(token, 1, T_OR))
	{
		op = extract_cmp_op((*token)->prev);
		right = parse_pipe(token, status);
		if (right == NULL)
			return (ast_free(left), NULL);
		cmd = cmd_cmp_init(op, left, right, NULL);
		if (cmd == NULL)
			return (ast_free(left), ast_free(right), NULL);
		if (left != cmd)
		{
			left->parent = cmd;
			right->parent = cmd;
		}
		left = cmd;
	}
	return (left);
}

t_cmd	*parse_program_bonus(t_token **token, int *status)
{
	if (token == NULL || *token == NULL)
		return (NULL);
	if ((*token)->type == T_EOF)
		return (NULL);
	return (parse_compound(token, status));
}
