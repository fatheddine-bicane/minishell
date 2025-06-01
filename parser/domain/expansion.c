/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansoin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/10/25 22:21:05 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

char	*param_expand(char *src)
{
	size_t			i;
	size_t			offset;
	size_t			start;
	t_str_builder	*sb;

	// int	quote_start;
	// int	quote_end;
	// quote_start = 0;
	// quote_end = 0;
	// bool is_quoted = false;
	// while (src[i])
	// {
	// 	if (src[i] == '"')
	// 	{
	// 		quote_start = i++;
	// 		while (src[i] && src[i] != '"')
	// 			i++;
	// 		quote_end = i;
	// 	}
	// 	i++;
	// }
	i = 0;
	if (!src[i])
		return (src);
	sb = sb_create(10);
	start = 0;
	while (src[i])
	{
		if (src[i] == '$' && is_name(src, i + 1))
		{
			if (i > start)
				sb_append_str(sb, src + start, i - start);
			offset = i + 1;
			i += 1;
			while (is_name(src, i))
				i++;
			sb_append_str(sb, src + offset, i - offset);
			printf("substr = %s\n", sb->buff[sb_len(sb) - 1]);
			offset = 0;
			start = i;
			continue ;
		}
		i++;
	}
	if (i > start)
		sb_append_str(sb, src + start, i - start);
	free(src);
	return (sb_build_str(sb));
}
