/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sn_printf_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:41:52 by klaayoun          #+#    #+#             */
/*   Updated: 2024/11/22 13:41:54 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

char	*sn_strchr(const char *s, int c)
{
	while (*s && *s != (char)c)
		s++;
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

int	sn_putchr(char c)
{
	return (write(STDOUT_FILENO, &c, 1));
}

int	sn_putchr_fd(char c, int fd)
{
	return (write(fd, &c, 1));
}

int	sn_putstr(char *s)
{
	int	i;

	if (!s)
		s = "(null)";
	i = 0;
	while (s[i])
		i++;
	write(STDOUT_FILENO, s, i);
	return (i);
}

int	sn_putstr_fd(char *str, int fd)
{
	return (write(fd, str, sn_strlen(str)));
}
