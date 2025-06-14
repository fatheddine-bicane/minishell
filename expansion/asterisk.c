/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asterisk.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/10/25 22:21:05 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishel.h"
#include <dirent.h>

bool	is_skippable(char *d_name)
{
	size_t	len;

	len = 0;
	while (d_name[len])
	{
		if (len > 2)
			return (false);
		len++;
	}
	if (len == 1 && d_name[0] == '.')
		return (true);
	if (len == 2 && d_name[0] == '.' && d_name[1] == '.')
		return (true);
	return (false);
}

char	**collect_files(char *pathname)
{
	DIR				*dir;
	struct dirent	*ent;
	t_str_builder	*sb;

	dir = opendir(pathname);
	if (dir == NULL)
		return (sn_eprintf("ERORR: could not open directory %c: %s\n", '.',
				strerror(errno)), NULL);
	sb = sb_create(10);
	if (sb == NULL)
		return (closedir(dir), NULL);
	ent = readdir(dir);
	while (ent != NULL)
	{
		if (is_skippable(ent->d_name))
		{
			ent = readdir(dir);
			continue ;
		}
		if (!sb_append_str(sb, ent->d_name, 0))
			return (sb_free(sb), closedir(dir), NULL);
		ent = readdir(dir);
	}
	return (closedir(dir), sb_build(sb));
}

void	asterisk(void)
{
	char	**files;
	size_t	i;

	files = collect_files(".");
	if (files == NULL)
		return ;
	i = 0;
	while (files[i])
	{
		sn_printf("[%d] %s\n", i, files[i]);
		i++;
	}
	sn_strs_free(files);
}
