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

char	**asterisk(char **argv, size_t *i)
{
	char			**files;
	char			*pattern;
	size_t			j;
	t_str_builder	*sb;

	pattern = argv[*i];
	sn_printf("pattern = `%s`\n", pattern);
	files = collect_files(".");
	if (files == NULL)
		return (NULL);
	sb = sb_create(10);
	if (sb == NULL)
		return (sn_strs_free(files), NULL);
	if (sn_strncmp(pattern, "*", sn_strlen(pattern)) == 0)
	{
		j = 0;
		while (j < *i)
			if (!sb_append_str(sb, argv[j++], 0))
				return (sb_free(sb), sn_strs_free(files), NULL);
		j = 0;
		while (files[j])
			if (!sb_append_str(sb, files[j++], 0))
				return (sb_free(sb), sn_strs_free(files), NULL);
		j = j + *i;
		while (argv[++(*i)])
		{
			if (!sb_append_str(sb, argv[*i], 0))
				return (sb_free(sb), sn_strs_free(files), NULL);
		}
		*i = j - 1;
		return (sn_strs_free(files), sb_build(sb));
	}
	return (sn_strs_free(files), NULL);
}
