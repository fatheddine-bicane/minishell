/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sn_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/10/25 22:21:05 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsn.h"

char	*sn_strjoin(char *start, char *end, char join)
{
	char	*result;
	size_t	i;
	size_t	j;

	if (start == NULL || end == NULL)
		return (NULL);
	result = malloc(sizeof(char) * sn_strlen(start) + sn_strlen(end) + 2);
	if (result == NULL)
		return (NULL);
	i = 0;
	while (start[i])
	{
		result[i] = start[i];
		i++;
	}
	result[i++] = join;
	j = 0;
	while (end[j])
		result[i++] = end[j++];
	result[i] = '\0';
	return (result);
}
