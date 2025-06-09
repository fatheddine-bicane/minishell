/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/10/25 22:21:05 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

int		extract_redirect_type(t_token **token);
char	*extract_filename(t_token **token);
bool	append_lexeme(t_str_builder *sb, t_token *t);
t_cmd	*append_redirect(t_cmd *root, t_cmd *new);
t_cmd	*combine_cmd(t_str_builder *sb, t_cmd *cmd);

t_cmd	*parse_io_redirect(t_token **token, int *status)
{
	int		type;
	char	*file;

	if (match_token(token, 4, T_REDIR_IN, T_REDIR_OUT, T_REDIR_OUT_APPEND,
			T_HEREDOC))
	{
		if (!match_token(token, 4, T_WORD, T_VAR, T_STR_DOUBLE, T_STR_SINGLE))
			return ((*status = -1), NULL);
		type = extract_redirect_type(token);
		file = extract_filename(token);
		if (file == NULL)
			return ((*status = -1), NULL);
		return (cmd_redirect_init(type, file, NULL, NULL));
	}
	return (NULL);
}

t_cmd	*parse_redirect(t_token **token, int *status)
{
	t_cmd	*cmd;
	t_cmd	*left;
	t_cmd	*right;

	left = parse_io_redirect(token, status);
	if (left == NULL || *status == -1)
		return (NULL);
	cmd = left;
	while (match_token(token, 4, T_REDIR_IN, T_REDIR_OUT, T_REDIR_OUT_APPEND,
			T_HEREDOC))
	{
		*token = (*token)->prev;
		if ((*token)->type == T_BLANK)
			*token = (*token)->prev;
		right = parse_io_redirect(token, status);
		if (right == NULL || *status == -1)
			return (ast_free(left), ast_free(right), NULL);
		cmd->u_as.redirect.next = right;
		right->parent = cmd;
		cmd = right;
	}
	return (left);
}

t_cmd	*parse_cmd(t_token **token, int *status)
{
	t_str_builder	*sb;
	t_cmd			*cmd;

	cmd = parse_redirect(token, status);
	if (*status == -1)
		return (NULL);
	sb = sb_create(10);
	while (match_token(token, 4, T_WORD, T_VAR, T_STR_SINGLE, T_STR_DOUBLE))
	{
		if (!append_lexeme(sb, (*token)->prev))
			return ((*status = -1), sb_free(sb), ast_free(cmd), NULL);
		cmd = append_redirect(cmd, parse_redirect(token, status));
		if (*status == -1)
			return (sb_free(sb), ast_free(cmd), NULL);
	}
	return (combine_cmd(sb, cmd));
}
