/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sn_sb_nbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/10/25 22:21:05 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsn.h"

bool	sb_append_nbr(t_str_builder *sb, int n)
{
	long	num;

	num = n;
	if (num < 0)
	{
		if (!sb_append_char(sb, '-'))
			return (false);
		num *= -1;
	}
	if (num > 9)
	{
		if (!sb_append_nbr(sb, num / 10))
			return (false);
		return (sb_append_char(sb, num % 10 + '0'));
	}
	else
		return (sb_append_char(sb, num + '0'));
}

bool	sb_append_unbr(t_str_builder *sb, unsigned int n)
{
	if (n > 9)
	{
		if (!sb_append_unbr(sb, n / 10))
			return (false);
		return (sb_append_char(sb, n % 10 + '0'));
	}
	else
		return (sb_append_char(sb, n + '0'));
}

bool	sb_append_hex(t_str_builder *sb, unsigned long num, int uppercase)
{
	char	*hex;

	hex = "0123456789abcdef";
	if (uppercase == 1)
		hex = "0123456789ABCDEF";
	if (num > 15)
	{
		if (!sb_append_hex(sb, num / 16, uppercase))
			return (false);
		return (sb_append_char(sb, hex[num % 16]));
	}
	else
		return (sb_append_char(sb, hex[num]));
}

bool	sb_append_ptr(t_str_builder *sb, void *ptr)
{
	if (ptr == NULL)
		return (sb_append_str(sb, "(nil)", 0));
	if (!sb_append_str(sb, "0x", 2))
		return (false);
	return (sb_append_hex(sb, (unsigned long)ptr, 0));
}
