/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sn_printf_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:41:52 by klaayoun          #+#    #+#             */
/*   Updated: 2024/11/22 13:41:54 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsn.h"

static bool	handle_str(va_list args, t_str_builder *sb)
{
	char	*str;

	str = va_arg(args, char *);
	if (str == NULL)
		str = "(null)";
	return (sb_append_str(sb, str, 0));
}

static int	process_specifier(va_list args, t_str_builder *sb, char specifier)
{
	int		bytes;
	bool	r;

	bytes = sb_total_size(sb);
	r = false;
	if (specifier == '%')
		r = sb_append_char(sb, '%');
	else if (specifier == 'c')
		r = sb_append_char(sb, va_arg(args, int));
	else if (specifier == 's')
		r = handle_str(args, sb);
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
	return (sb_total_size(sb) - bytes);
}

int	sn_print_parse(va_list ap, t_str_builder *sb, const char *s, size_t *i)
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
		specifier_bytes = process_specifier(ap, sb, *specifier);
		if (specifier_bytes == -1)
			return (-1);
		*i += 2;
		bytes += specifier_bytes;
	}
	return (bytes);
}
