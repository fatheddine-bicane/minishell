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
	char	**new_buff;
	size_t	i;

	if (sb == NULL || sb->buff == NULL || len == 0)
		return (false);
	if (sb->cap >= sb->len + len + 1)
		return (true);
	while (sb->cap < sb->len + len + 1)
	{
		sb->cap <<= 1;
		if (sb->cap == 0)
			sb->cap--;
	}
	new_buff = malloc(sizeof(char *) * sb->cap);
	if (new_buff == NULL)
		return (false);
	i = 0;
	while (i < sb->len)
	{
		new_buff[i] = sb->buff[i];
		i++;
	}
	free(sb->buff);
	sb->buff = new_buff;
	return (true);
}

size_t	sb_len(t_str_builder *sb)
{
	if (sb == NULL || sb->buff == NULL)
		return (0);
	return (sb->len);
}

size_t	sb_total_size(t_str_builder *sb)
{
	if (sb == NULL || sb->buff == NULL)
		return (0);
	return (sb->total_size);
}
