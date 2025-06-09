/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sn_sprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:41:52 by klaayoun          #+#    #+#             */
/*   Updated: 2024/11/22 13:41:54 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsn.h"

static t_str_builder	*inner_buff_init(char **buff, const char *fmt)
{
	t_str_builder	*sb;

	if (!buff || !fmt)
		return (NULL);
	sb = sb_create(10);
	if (sb == NULL)
		return (NULL);
	return (sb);
}

int	sn_vsprintf(va_list args, char **buff, const char *fmt, ...)
{
	int				bytes;
	int				r;
	size_t			i;
	size_t			start;
	t_str_builder	*sb;

	sb = inner_buff_init(buff, fmt);
	if (sb == NULL)
		return (sb_free(sb), -1);
	bytes = 0;
	i = 0;
	while (fmt[i])
	{
		start = i;
		while (fmt[i] && fmt[i] != '%')
			i++;
		if (i - start > 0 && !sb_append_str(sb, fmt + start, i - start))
			return (*buff = NULL, sb_free(sb), -1);
		bytes += i - start;
		r = sn_print_parse(args, sb, fmt, &i);
		if (r == -1)
			return (*buff = NULL, sb_free(sb), -1);
		bytes += r;
	}
	return (*buff = sb_build_str(sb), bytes);
}

int	sn_sprintf(char **buff, const char *format, ...)
{
	int		bytes;
	va_list	args;

	if (!format || !buff)
		return (-1);
	va_start(args, format);
	bytes = sn_vsprintf(args, buff, format);
	va_end(args);
	return (bytes);
}
