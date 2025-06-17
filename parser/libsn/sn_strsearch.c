/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sn_strsearch.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/10/25 22:21:05 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

char	*sn_strsearch(char *haystack[], char *needle)
{
	int	i;
	int	n;

	if (haystack == NULL || needle == NULL)
		return (NULL);
	n = sn_strlen(needle);
	i = 0;
	while (haystack[i] != NULL)
	{
		if (sn_strncmp(haystack[i], needle, n) == 0)
			return (haystack[i]);
		i++;
	}
	return (NULL);
}
