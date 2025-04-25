/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sn_readfile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/10/25 22:21:05 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsn.h"

char	*sn_readfile(char *file)
{
	int			fd;
	char		*buf;
	struct stat	stats;
	ssize_t		bytes;
	ssize_t		total_bytes;

	total_bytes = 0;
	stats = (struct stat){};
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (NULL);
	if (stat(file, &stats) == -1)
		return (close(fd), NULL);
	buf = malloc(sizeof(char) * stats.st_size + 1);
	if (buf == NULL)
		return (close(fd), NULL);
	while (total_bytes < stats.st_size)
	{
		bytes = read(fd, buf + total_bytes, stats.st_size - total_bytes);
		if (bytes == -1)
			return (close(fd), free(buf), NULL);
		total_bytes += bytes;
	}
	buf[total_bytes] = '\0';
	return (close(fd), buf);
}
