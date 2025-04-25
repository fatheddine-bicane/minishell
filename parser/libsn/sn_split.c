/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sn_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/10/25 22:21:05 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsn.h"

char	**sn_split_free(char **arr)
{
	char	**t;

	if (arr == NULL)
		return (NULL);
	t = arr;
	while (*t != NULL)
		free(*t++);
	free(arr);
	return (NULL);
}

static char	**sn_allocate(char **lst, char const *s, char sep)
{
	char		**t;
	char const	*tmp;

	tmp = s;
	t = lst;
	while (*tmp)
	{
		while (*s == sep)
			++s;
		tmp = s;
		while (*tmp && *tmp != sep)
			++tmp;
		if (*tmp == sep || tmp > s)
		{
			*t = sn_substr(s, 0, tmp - s);
			if (*t == NULL)
				return (sn_split_free(lst));
			s = tmp;
			++t;
		}
	}
	*t = NULL;
	return (lst);
}

static int	sn_count_words(char const *s, char sep)
{
	int	word_count;

	word_count = 0;
	while (*s)
	{
		while (*s == sep)
			++s;
		if (*s)
			++word_count;
		while (*s && *s != sep)
			++s;
	}
	return (word_count);
}

char	**sn_split(char const *s, char c)
{
	char	**new;
	int		size;

	if (!s)
		return (NULL);
	size = sn_count_words(s, c);
	new = (char **)malloc(sizeof(char *) * (size + 1));
	if (!new)
		return (NULL);
	return (sn_allocate(new, s, c));
}
