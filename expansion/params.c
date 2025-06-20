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

bool	expand_var(t_shell *shell, t_str_builder *sb, char *var, size_t len);
bool	word_split(char *ifs, char ***args, size_t *i);
size_t	word_count(char *src, char *sep);
char	*get_ifs_var(t_list *envp);
void	clean_args_leftover(char **args, size_t i);
bool	should_split_words(char *src, char *expanded_src);

bool	extract_quote_param(t_shell *shell, t_str_builder *sb, char *str,
		size_t len)
{
	size_t	i;
	size_t	offset;

	i = 0;
	offset = 0;
	while (str[i] && i < len)
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

bool	param_extract(t_token *t, t_str_builder *sb, t_shell *shell, char **ifs)
{
	size_t	len;

	len = sn_strlen(t->lexeme);
	if (t->type == T_STR_SINGLE || t->type == T_STR_DOUBLE)
	{
		if (len == 2)
			return (sb_append_char(sb, '\0'));
		if (t->type == T_STR_SINGLE)
			return (sb_append_str(sb, t->lexeme + 1, len - 2));
		if (t->prev && t->prev->prev && t->prev->prev->type == T_VAR)
			*ifs = NULL;
		return (extract_quote_param(shell, sb, t->lexeme + 1, len - 2));
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
	return (sb_append_str(sb, t->lexeme, len));
}

char	*param_scan(char *src, t_shell *shell, char **ifs)
{
	t_str_builder	*sb;
	t_token			*token;
	t_token			*head;
	char			*scan_err;

	scan_err = NULL;
	token = tokens_scan(src, &scan_err);
	if (token == NULL || scan_err != NULL)
		return (sn_eprintf(scan_err), free(scan_err), tokens_free(token), NULL);
	head = token;
	if (is_end(head))
		return (tokens_free(head), sn_strdup(src));
	sb = sb_create(10);
	if (sb == NULL)
		return (tokens_free(head), NULL);
	while (token && token->type != T_EOF)
	{
		if (!param_extract(token, sb, shell, ifs))
			return (tokens_free(head), sb_free(sb), NULL);
		token = token->next;
	}
	return (tokens_free(head), sb_build_str(sb));
}

char	*expand_single_param(char *src, t_shell *shell)
{
	char	*result;
	char	*ifs;
	size_t	count;
	char	**args;

	ifs = NULL;
	result = param_scan(src, shell, &ifs);
	if (result == NULL)
		return (free(src), NULL);
	if (ifs == NULL)
		return (free(src), result);
	count = word_count(result, ifs);
	if (count == 0 || count > 1)
		return (free(src), free(result), NULL);
	count = 0;
	args = malloc(sizeof(char *) * 2);
	if (args == NULL)
		return (free(src), free(result), NULL);
	args[count] = result;
	args[count + 1] = NULL;
	if (!word_split(ifs, &args, &count))
		return (free(src), free(result), sn_strs_free(args), NULL);
	result = args[0];
	return (free(src), free(args), result);
}

bool	expand_params(char ***argvp, t_shell *shell)
{
	size_t	i;
	char	*src;
	char	*ifs;
	char	**argv;

	ifs = NULL;
	i = 0;
	argv = *argvp;
	while (argv[i] != NULL)
	{
		src = argv[i];
		argv[i] = param_scan(src, shell, &ifs);
		if (argv[i] == NULL)
			return (free(src), clean_args_leftover(argv, ++i), false);
		if (ifs != NULL)
		{
			if (should_split_words(src, argv[i]) && !word_split(ifs, argvp, &i))
				return (free(src), clean_args_leftover(argv, i), false);
			argv = *argvp;
			ifs = NULL;
		}
		free(src);
		i++;
	}
	return (true);
}
