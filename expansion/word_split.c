/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/10/25 22:21:05 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"

bool	is_sep(char *sep, char c)
{
	size_t	i;

	i = 0;
	while (sep[i])
	{
		if (sep[i] == c)
			return (true);
		i++;
	}
	return (false);
}

size_t	word_count(char *src, char *sep)
{
	size_t	word_count;
	size_t	i;

	word_count = 0;
	i = 0;
	while (src[i])
	{
		while (is_sep(sep, src[i]))
			i++;
		if (src[i])
			word_count++;
		while (src[i] && !is_sep(sep, src[i]))
			i++;
	}
	return (word_count);
}

bool	sn_word_split(t_str_builder *sb, char const *s, char *sep)
{
	char const	*tmp;

	tmp = s;
	while (*tmp)
	{
		while (is_sep(sep, *s))
			++s;
		tmp = s;
		while (*tmp && !is_sep(sep, *tmp))
			++tmp;
		if (is_sep(sep, *tmp) || tmp > s)
		{
			if (!sb_append_str(sb, s, tmp - s))
				return (false);
			s = tmp;
		}
	}
	return (true);
}

bool	word_split(char *ifs, char ***argvp, size_t *i)
{
	t_str_builder	*sb;
	char			**argv;
	size_t			count;
	size_t			j;
	size_t			before;

	argv = *argvp;
	count = word_count(argv[*i], ifs);
	if (count == 0)
		return (sn_bzero(argv[*i], sn_strlen(argv[*i])), true);
	sb = sb_create(*i + count + 1);
	if (sb == NULL)
		return (false);
	j = 0;
	while (j < *i)
		if (!sb_append_str(sb, argv[j++], 0))
			return (sb_free(sb), false);
	if (!sn_word_split(sb, argv[*i], ifs))
		return (sb_free(sb), false);
	before = sb_len(sb) - 1;
	while (argv[++(*i)])
		if (!sb_append_str(sb, argv[*i], 0))
			return (sb_free(sb), false);
	*i = before;
	return (sn_strs_free(argv), *argvp = sb_build(sb), true);
}

bool	should_split_words(char *src, char *expanded_src)
{
	char *eq = sn_strchr(expanded_src, '=');
	if (src == NULL || expanded_src == NULL)
		return (false);
	if (src[0] != '$' && eq != NULL)
		return (false);
	return (true);
}
