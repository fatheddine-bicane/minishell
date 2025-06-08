/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/10/25 22:21:05 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

bool	expand_var(t_shell *shell, t_str_builder *sb, char *variable,
			size_t len);
char	*get_ifs_var(t_list *envp);

bool	parse_quote_param(t_shell *shell, t_str_builder *sb, char *str,
		size_t len)
{
	size_t	i;
	size_t	offset;

	i = 1;
	offset = 1;
	while (str[i] && i < len - 1)
	{
		if (str[i] == '$' && (str[i + 1] == '?' || is_name(str, i + 1)))
		{
			if (i > offset && !sb_append_str(sb, str + offset, i - offset))
				return (false);
			offset = i + 1;
			i += 2;
			while (is_name(str, i) && str[offset] != '?')
				i++;
			if (!expand_var(shell, sb, str + offset, i - offset))
				return (false);
			offset = i;
			continue ;
		}
		i++;
	}
	if (i > offset)
		return (sb_append_str(sb, str + offset, i - offset));
	return (true);
}

bool	parse_param(t_token *t, t_str_builder *sb, t_shell *shell, char **ifs)
{
	size_t	len;

	len = sn_strlen(t->lexeme);
	if (t->type == T_STR_SINGLE)
	{
		if (len == 2)
			return (sb_append_char(sb, '\0'));
		return (sb_append_str(sb, t->lexeme + 1, len - 2));
	}
	if (t->type == T_VAR)
	{
		if (!expand_var(shell, sb, t->lexeme + 1, len - 1))
			return (false);
		if (*sb_str_at(sb, sb_len(sb) - 1) == '\0')
			return (true);
		*ifs = get_ifs_var(shell->my_envp);
		return (true);
	}
	if (t->type == T_STR_DOUBLE)
	{
		if (len == 2)
			return (sb_append_char(sb, '\0'));
		return (parse_quote_param(shell, sb, t->lexeme, len));
	}
	return (sb_append_str(sb, t->lexeme, len));
}

char	*param_expand(char *src, t_shell *shell, char **ifs)
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
		if (!parse_param(token, sb, shell, ifs))
			return (tokens_free(head), sb_free(sb), NULL);
		token = token->next;
	}
	return (tokens_free(head), sb_build_str(sb));
}

bool	word_split(char *ifs, char **args, size_t i)
{
	size_t	word_count;
	size_t	j;
	size_t	k;

	word_count = 0;
	j = 0;
	while (args[i][j])
	{
		k = 0;
		while (ifs[k])
		{
			if (args[i][j] == ifs[k])
			{
				word_count++;
				while (args[i][j] && args[i][j] == ifs[k])
					j++;
			}
			k++;
		}
		j++;
	}
	if (word_count == 0)
		return (true);
	sn_printf("IFS = `%s`\n", ifs);
	sn_printf("target = `%s`\n", args[i]);
	sn_printf("word count = %d\n", word_count);
	return (true);
}

void	clean_args(char **args, size_t i)
{
	while (args[i] != NULL)
	{
		free(args[i]);
		args[i++] = NULL;
	}
}

// NOTE(karim): // maybe reuse src if expansion fails
bool	expand_params(char **args, t_shell *shell)
{
	size_t	i;
	char	*src;
	char	*ifs;

	if (args == NULL)
		return (false);
	ifs = NULL;
	i = 0;
	while (args[i] != NULL)
	{
		src = args[i];
		args[i] = param_expand(src, shell, &ifs);
		free(src);
		if (args[i] == NULL)
			return (clean_args(args, ++i), false);
		if (ifs != NULL)
		{
			if (!word_split(ifs, args, i))
				return (clean_args(args, i), false);
			ifs = NULL;
		}
		i++;
	}
	return (true);
}
