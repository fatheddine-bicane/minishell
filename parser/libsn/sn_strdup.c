/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sn_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/10/25 22:21:05 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

char	*sn_strdup(const char *s)
{
	char	*dup;
	size_t	len;

	len = sn_strlen(s) + 1;
	dup = (char *)malloc(sizeof(char) * len);
	if (dup == NULL)
		return (NULL);
	return ((char *)sn_memcpy(dup, s, len));
}
