/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sn_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/10/25 22:21:05 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

int	sn_isspace(char c)
{
	return (c == '\t' || c == '\f' || c == '\n' || c == '\v' || c == '\r'
		|| c == ' ');
}

int	sn_atoi(const char *nptr, int *num)
{
	int	r;
	int	s;
	int	prev;

	r = 0;
	s = 1;
	while (sn_isspace(*nptr))
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			s = -1;
		nptr++;
	}
	while (sn_isdigit(*nptr))
	{
		prev = r;
		r = (r * 10) + (*nptr++ - '0') * s;
		if (r / 10 != prev)
			return (-1);
	}
	*num = r;
	return (0);
}
