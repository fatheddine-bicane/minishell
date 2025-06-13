/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/10/25 22:21:05 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

bool		expand_var(t_shell *shell, t_str_builder *sb, char *var,
				size_t len);
bool		has_quote(char *src);
bool		extract_quote_param(t_shell *shell, t_str_builder *sb, char *str,
				size_t len);

static bool	param_extract(t_token *t, t_str_builder *sb, t_shell *shell,
		t_exp_flags flags)
{
	size_t	len;

	len = sn_strlen(t->lexeme);
	if (t->type == T_STR_SINGLE || t->type == T_STR_DOUBLE)
	{
		if (flags & EXP_IS_DLIMITER)
		{
			if (len == 2)
				return (sb_append_char(sb, '\0'));
			return (sb_append_str(sb, t->lexeme + 1, len - 2));
		}
		if ((flags & EXP_IS_QUOTED) == 0)
			return (extract_quote_param(shell, sb, t->lexeme, len));
		return (sb_append_str(sb, t->lexeme, len));
	}
	if (t->type == T_VAR && flags & EXP_IS_BODY && (flags & EXP_IS_QUOTED) == 0)
	{
		if (!expand_var(shell, sb, t->lexeme + 1, len - 1))
			return (false);
		if (*sb_str_at(sb, sb_len(sb) - 1) == '\0')
			return (true);
		return (true);
	}
	return (sb_append_str(sb, t->lexeme, len));
}

char	*heredoc_scan(char *src, t_shell *shell, t_exp_flags flags)
{
	t_str_builder	*sb;
	t_token			*token;
	t_token			*head;

	token = tokens_scan(src);
	if (token == NULL)
		return (NULL);
	head = token;
	sb = sb_create(10);
	if (sb == NULL)
		return (tokens_free(head), NULL);
	while (token && token->type != T_EOF)
	{
		if (!param_extract(token, sb, shell, flags))
			return (tokens_free(head), sb_free(sb), NULL);
		token = token->next;
	}
	return (tokens_free(head), sb_build_str(sb));
}

char	*expand_heredoc_delimiter(char *src, t_shell *shell)
{
	char	*result;

	result = heredoc_scan(src, shell, EXP_IS_DLIMITER);
	return (result);
}

char	*expand_heredoc_body(char *src, t_shell *shell, bool is_quoted)
{
	char	*result;

	if (src == NULL)
		return (NULL);
	if (src[0] == '\0')
		return (src);
	if (is_quoted)
		result = heredoc_scan(src, shell, EXP_IS_BODY | EXP_IS_QUOTED);
	else
		result = heredoc_scan(src, shell, EXP_IS_BODY);
	return (free(src), result);
}
