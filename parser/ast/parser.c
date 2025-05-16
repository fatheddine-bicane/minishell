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

t_cmd	*parse_program(t_token **token);
t_cmd	*parse_cmd(t_token **token);

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
			sn_printf_fd(STDERR_FILENO, "Expect ')' to end subshell.");
			return (cmd_free(cmd), NULL);
		}
		return (cmd);
	}
	return (parse_cmd(token));
}

t_cmd	*parse_io_redirect(t_token **token)
{
	(void)token;
	return (NULL);
}

t_cmd	*parse_redirect(t_token **token)
{
	t_cmd	*cmd;
	t_cmd	*next;

	if (match_token(token, 1, T_REDIR_IN))
	{
		if (!match_token(token, 5, T_WORD, T_VAR, T_STR_SINGLE, T_STR_DOUBLE))
		{
			sn_printf_fd(STDERR_FILENO,
				"syntax error near unexpected token `%s`", (*token)->lexeme);
			return (NULL);
		}
		next = parse_redirect(token);
		cmd = cmd_redirect_init(R_REDIR_IN, sn_strdup((*token)->prev->lexeme),
				next);
		if (cmd == NULL)
			return (cmd_free(next), NULL);
		return (cmd);
	}
	return (parse_group(token));
}

t_cmd	*parse_cmd(t_token **token)
{
	char	**argv;
	int		matches;
	int		i;
	t_token	*current;

	if (match_token(token, 5, T_WORD, T_VAR, T_STR_SINGLE, T_STR_DOUBLE))
	{
		matches = 1;
		current = (*token)->prev;
		while (match_token(token, 5, T_WORD, T_VAR, T_STR_SINGLE, T_STR_DOUBLE))
			matches++;
		argv = malloc(sizeof(char *) * matches + 1);
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
	return (NULL);
}

t_cmd	*parse_pipe(t_token **token)
{
	t_cmd	*cmd;
	t_cmd	*left;
	t_cmd	*right;

	left = parse_cmd(token);
	if (left == NULL)
		return (NULL);
	while (match_token(token, 1, T_PIPE))
	{
		right = parse_cmd(token);
		if (right == NULL)
			return (cmd_free(left), NULL);
		cmd = cmd_pipe_init(left, right);
		if (cmd == NULL)
			return (cmd_free(left), cmd_free(right), NULL);
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
	return (parse_pipe(token));
}
