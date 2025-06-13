/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_msg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/10/25 22:21:05 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsn.h"

ssize_t	set_msg(char **msg, const char *format, ...)
{
	va_list	args;
	ssize_t	bytes;

	if (msg == NULL)
		return (-1);
	va_start(args, format);
	bytes = sn_sprintf(msg, format, args);
	va_end(args);
	return (bytes);
}
