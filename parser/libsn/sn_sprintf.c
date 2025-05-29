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

static int	parse(va_list ap, t_str_builder *sb, const char *s, size_t *i)
{
	char	*specifier;
	int		specifier_bytes;
	int		bytes;

	bytes = 0;
	if (!s[*i])
		return (bytes);
	specifier = sn_strchr("cspdiuxX%", s[*i + 1]);
	if (!specifier)
	{
		if (!sb_append_char(sb, '%'))
			return (-1);
		bytes++;
	}
	else
	{
		specifier_bytes = process(ap, sb, *specifier);
		if (specifier_bytes == -1)
			return (-1);
		*i += 2;
		bytes += specifier_bytes;
	}
	return (bytes);
}

static t_str_builder	*inner_buff_init(char **buff, const char *fmt)
{
	t_str_builder	*sb;

	if (!buff || !fmt)
		return (NULL);
	sb = sb_create(sn_strlen(fmt));
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
		r = parse(args, sb, fmt, &i);
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
