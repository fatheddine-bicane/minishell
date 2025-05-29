/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sn_sb_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/10/25 22:21:05 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsn.h"

bool	sb_append_str(t_str_builder *sb, const char *str, size_t len)
{
	if (sb == NULL || sb->buff == NULL || str == NULL)
		return (false);
	if (*str == '\0')
		return (true);
	if (len == 0)
		len = sn_strlen(str);
	if (!sb_ensure_size(sb, 1))
		return (false);
	sb->buff[sb->len] = sn_strndup(str, len);
	if (sb->buff[sb->len] == NULL)
		return (false);
	sb->total_size += len;
	sb->buff[++sb->len] = NULL;
	return (true);
}

const char	*sb_str(t_str_builder *sb, size_t index)
{
	if (sb == NULL || sb->buff == NULL)
		return (NULL);
	return (sb->buff[index]);
}

bool	sb_append_char(t_str_builder *sb, char c)
{
	if (sb == NULL || sb->buff == NULL)
		return (false);
	if (!sb_ensure_size(sb, 1))
		return (false);
	sb->buff[sb->len] = sn_strndup(&c, 1);
	if (sb->buff[sb->len] == NULL)
		return (false);
	sb->buff[++sb->len] = NULL;
	sb->total_size++;
	return (true);
}

char	**sb_split(t_str_builder *sb, char c)
{
	char	*text;
	char	**strs;

	text = sb_build_str(sb);
	if (text == NULL)
		return (NULL);
	strs = sn_split(text, c);
	if (strs == NULL)
		return (free(text), NULL);
	return (free(text), strs);
}
