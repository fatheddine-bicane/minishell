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

int	get_redirect_type(t_token **token)
{
	t_token	*t;

	t = *token;
	while (!is_redirect(t))
		t = t->prev;
	return (t->type);
}

t_cmd	*parse_io_redirect(t_token **token)
{
	int		type;
	char	*lexeme;
	char	*file;

	if (match_token(token, 4, T_REDIR_IN, T_REDIR_OUT, T_REDIR_OUT_APPEND,
			T_HEREDOC))
	{
		if (!match_token(token, 4, T_WORD, T_VAR, T_STR_DOUBLE, T_STR_SINGLE))
		{
			lexeme = extract_lexeme_err(*token);
			sn_eprintf("syntax error near unexpected token `%s`\n", lexeme);
			return (NULL);
		}
		type = get_redirect_type(token);
		file = sn_strdup((*token)->prev->lexeme);
		return (cmd_redirect_init(type, file, NULL));
	}
	lexeme = extract_lexeme_err(*token);
	sn_eprintf("syntax error near unexpected token `%s`\n", lexeme);
	return (NULL);
}

t_cmd	*parse_redirect(t_token **token)
{
	t_cmd	*cmd;
	t_cmd	*left;
	t_cmd	*right;

	left = parse_io_redirect(token);
	if (left == NULL)
		return (NULL);
	cmd = left;
	while (match_token(token, 4, T_REDIR_IN, T_REDIR_OUT, T_REDIR_OUT_APPEND,
			T_HEREDOC))
	{
		*token = (*token)->prev;
		if ((*token)->type == T_BLANK)
			*token = (*token)->prev;
		right = parse_io_redirect(token);
		if (right == NULL)
			return (ast_free(left), NULL);
		cmd->u_as.redirect.next = right;
		cmd = right;
	}
	return (left);
}

t_cmd	*parse_cmd(t_token **token)
{
	char	**argv;
	int		matches;
	int		i;
	t_token	*current;

	if (match_token(token, 4, T_WORD, T_VAR, T_STR_SINGLE, T_STR_DOUBLE))
	{
		matches = 1;
		current = (*token)->prev;
		while (match_token(token, 4, T_WORD, T_VAR, T_STR_SINGLE, T_STR_DOUBLE))
			matches++;
		argv = malloc(sizeof(char *) * (matches + 1));
		if (argv == NULL)
			return (NULL);
		i = 0;
		while (i < matches)
		{
			argv[i] = sn_strdup(current->lexeme);
			if (argv[i] == NULL)
				return (sn_strs_free(argv), NULL);
			current = current->next;
			if (current->type == T_BLANK)
				current = current->next;
			i++;
		}
		argv[matches] = NULL;
		return (cmd_exec_init(argv));
	}
	return (parse_redirect(token));
}

t_cmd	*parse_group(t_token **token)
{
	t_cmd	*cmd;

	if (match_token(token, 1, T_LEFT_PAREN))
	{
		cmd = cmd_group_init(parse_program(token));
		if (cmd == NULL)
			return (NULL);
		if (!match_token(token, 1, T_RIGHT_PAREN))
		{
			sn_eprintf("Expect ')' to end subshell.\n");
			return (ast_free(cmd), NULL);
		}
		return (cmd);
	}
	return (parse_cmd(token));
}

t_cmd	*parse_pipe(t_token **token)
{
	t_cmd	*cmd;
	t_cmd	*left;
	t_cmd	*right;

	left = parse_group(token);
	if (left == NULL)
		return (NULL);
	while (match_token(token, 1, T_PIPE))
	{
		right = parse_group(token);
		if (right == NULL)
			return (ast_free(left), NULL);
		cmd = cmd_pipe_init(left, right);
		if (cmd == NULL)
			return (ast_free(left), ast_free(right), NULL);
		left = cmd;
	}
	return (left);
}

t_cmd	*parse_compound(t_token **token)
{
	t_cmd	*cmd;
	t_cmd	*left;
	t_cmd	*right;
	int		op;

	left = parse_pipe(token);
	if (left == NULL)
		return (NULL);
	while (match_token(token, 1, T_AND) || match_token(token, 1, T_OR))
	{
		op = extract_cmp_op((*token)->prev);
		right = parse_pipe(token);
		if (right == NULL)
			return (ast_free(left), NULL);
		cmd = cmd_cmp_init(op, left, right);
		if (cmd == NULL)
			return (ast_free(left), ast_free(right), NULL);
		left = cmd;
	}
	return (left);
}

t_cmd	*parse_program(t_token **token)
{
	if (token == NULL || *token == NULL)
		return (NULL);
	if ((*token)->type == T_EOF)
		return (NULL);
	return (parse_compound(token));
}
