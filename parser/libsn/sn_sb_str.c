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
	if (sb == NULL || str == NULL)
		return (false);
	if (*str == '\0')
		return (true);
	if (len == 0)
		len = sn_strlen(str);
	if (!sb_ensure_size(sb, len))
		return (false);
	sn_memmove(sb->buff + sb->len, str, len);
	sb->len += len;
	sb->buff[sb->len] = '\0';
	return (true);
}

bool	sb_append_char(t_str_builder *sb, char c)
{
	if (sb == NULL)
		return (false);
	if (!sb_ensure_size(sb, 1))
		return (false);
	sb->buff[sb->len++] = c;
	sb->buff[sb->len] = '\0';
	return (true);
}

void	sb_drop(t_str_builder *sb, size_t len)
{
	if (sb == NULL || len == 0)
		return ;
	if (len >= sb->len)
	{
		sb_clear(sb);
		return ;
	}
	sb->len -= len;
	sn_memmove(sb->buff, sb->buff + len, sb->len + 1);
}

char	**sb_split(t_str_builder *sb, char c)
{
	char	*text;
	char	**strs;

	text = sb_build(sb);
	if (text == NULL)
		return (NULL);
	strs = sn_split(text, c);
	if (strs == NULL)
		return (free(text), NULL);
	return (free(text), strs);
}
