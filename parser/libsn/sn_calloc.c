/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sn_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/10/25 22:21:05 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

void	*sn_calloc(size_t nmemb, size_t size)
{
	void	*ret;
	size_t	total;

	total = nmemb * size;
	if (total == 0)
		return (malloc(0));
	if (total / size != nmemb)
		return (NULL);
	ret = malloc(total);
	if (ret == NULL)
		return (NULL);
	sn_bzero(ret, total);
	return (ret);
}
