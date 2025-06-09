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
	sb->buff = malloc(sizeof(char *) * sb->cap);
	if (sb->buff == NULL)
		return (free(sb), NULL);
	sb->buff[0] = NULL;
	sb->len = 0;
	sb->total_size = 0;
	return (sb);
}

void	sb_free(t_str_builder *sb)
{
	if (sb == NULL)
		return ;
	if (sb->buff)
		sn_strs_free(sb->buff);
	sb->buff = NULL;
	sb->cap = 0;
	sb->len = 0;
	sb->total_size = 0;
	free(sb);
}

char	*sb_str_at(t_str_builder *sb, size_t i)
{
	if (sb == NULL || sb->buff == NULL)
		return (NULL);
	if (i >= sb->len)
		return (NULL);
	return (sb->buff[i]);
}

char	**sb_build(t_str_builder *sb)
{
	char	**str;

	if (sb == NULL || sb->buff == NULL || sb->buff[0] == NULL)
		return (sb_free(sb), NULL);
	str = sb->buff;
	free(sb);
	return (str);
}

char	*sb_build_str(t_str_builder *sb)
{
	char	*str;
	size_t	i;
	size_t	total;
	size_t	len;

	if (sb == NULL || sb->buff == NULL || sb->buff[0] == NULL)
		return (sb_free(sb), NULL);
	str = malloc(sb->total_size + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	total = 0;
	while (i < sb->len)
	{
		len = sn_strlen(sb->buff[i]);
		sn_memcpy(str + total, sb->buff[i], len);
		total += len;
		i++;
	}
	str[total] = '\0';
	return (sb_free(sb), str);
}
