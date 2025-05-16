/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sn_sb_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:41:52 by klaayoun          #+#    #+#             */
/*   Updated: 2024/11/22 13:41:54 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsn.h"

bool	sb_ensure_size(t_str_builder *sb, size_t len)
{
	char	*new_buff;

	if (sb == NULL || len == 0)
		return (false);
	if (sb->cap >= sb->len + len + 1)
		return (true);
	while (sb->cap < sb->len + len + 1)
	{
		sb->cap <<= 1;
		if (sb->cap == 0)
			sb->cap--;
	}
	new_buff = malloc(sb->cap);
	if (new_buff == NULL)
		return (false);
	sn_memcpy(new_buff, sb->buff, sb->len);
	free(sb->buff);
	sb->buff = new_buff;
	return (true);
}

void	sb_truncate(t_str_builder *sb, size_t len)
{
	if (sb == NULL || len >= sb->len)
		return ;
	sb->len = len;
	sb->buff[sb->len] = '\0';
}

void	sb_clear(t_str_builder *sb)
{
	if (sb == NULL)
		return ;
	sb_truncate(sb, 0);
}

size_t	sb_len(t_str_builder *sb)
{
	if (sb == NULL)
		return (0);
	return (sb->len);
}

const char	*sb_str(t_str_builder *sb)
{
	if (sb == NULL)
		return (NULL);
	return (sb->buff);
}
