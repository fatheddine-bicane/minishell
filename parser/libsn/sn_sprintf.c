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

static int	process(va_list args, t_str_builder *sb, char specifier)
{
	int		bytes;
	bool	r;

	bytes = sb->len;
	r = false;
	if (specifier == '%')
		r = sb_append_char(sb, '%');
	else if (specifier == 'c')
		r = sb_append_char(sb, va_arg(args, int));
	else if (specifier == 's')
		r = sb_append_str(sb, va_arg(args, char *), 0);
	else if (specifier == 'd' || specifier == 'i')
		r = sb_append_nbr(sb, va_arg(args, int));
	else if (specifier == 'u')
		r = sb_append_unbr(sb, va_arg(args, int));
	else if (specifier == 'x' || specifier == 'X')
		r = sb_append_hex(sb, va_arg(args, unsigned int), specifier == 'X');
	else if (specifier == 'p')
		r = sb_append_ptr(sb, va_arg(args, void *));
	if (!r)
		return (-1);
	return (sb->len - bytes);
}

static int	handle_specifier(va_list args, t_str_builder *sb, const char *s,
		size_t *i)
{
	char	*specifier;
	int		r;
	int		bytes;

	bytes = 0;
	specifier = sn_strchr("cspdiuxX%", s[*i + 1]);
	if (!specifier)
	{
		if (!sb_append_char(sb, '%'))
			return (-1);
		bytes++;
		s++;
	}
	else
	{
		r = process(args, sb, *specifier);
		if (r == -1)
			return (-1);
		*i += 2;
		bytes += r;
	}
	return (bytes);
}

int	sn_vsprintf(va_list args, char **buff, const char *fmt, ...)
{
	int				bytes;
	int				r;
	size_t			i;
	t_str_builder	*sb;

	sb = sb_create(sn_strlen(fmt));
	if (!fmt || !buff || sb == NULL)
		return (sb_free(sb), -1);
	bytes = 0;
	i = 0;
	while (fmt[i])
	{
		if (fmt[i] != '%' && ++bytes)
		{
			if (!sb_append_char(sb, fmt[i++]))
				return (*buff = NULL, sb_free(sb), -1);
			continue ;
		}
		r = handle_specifier(args, sb, fmt, &i);
		if (r == -1)
			return (*buff = NULL, sb_free(sb), -1);
		bytes += r;
	}
	return (*buff = sb_build(sb), bytes);
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
