/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sn_sb.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/10/25 22:21:05 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsn.h"

t_str_builder	*sb_create(size_t cap)
{
	t_str_builder	*sb;

	sb = sn_calloc(1, sizeof(t_str_builder));
	if (sb == NULL)
		return (NULL);
	sb->cap = 10;
	if (sb->cap < cap)
		sb->cap = cap;
	sb->buff = malloc(sb->cap);
	if (sb->buff == NULL)
		return (free(sb), NULL);
	sb->buff[0] = '\0';
	sb->len = 0;
	return (sb);
}

void	sb_free(t_str_builder *sb)
{
	if (sb == NULL)
		return ;
	if (sb->buff)
		free(sb->buff);
	sb->buff = NULL;
	sb->cap = 0;
	sb->len = 0;
	free(sb);
}

char	*sb_build(t_str_builder *sb)
{
	char	*str;

	if (sb == NULL)
		return (NULL);
	if (sb->buff == NULL)
		return (sb_free(sb), NULL);
	str = sn_strndup(sb->buff, sb->len);
	return (sb_free(sb), str);
}
