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

void	asterisk(void)
{
	DIR				*dir;
	struct dirent	*ent;
	t_str_builder *sb;

	dir = opendir(".");
	if (dir == NULL)
	{
		sn_eprintf("ERORR: could not open directory %c: %s\n", '.', strerror(errno));
		return ;
	}
	sb = sb_create(10);
	if (sb == NULL)
	{
		closedir(dir);
		return;
	}
	ent = readdir(dir);
	while (ent != NULL)
	{
		if (!sb_append_str(sb, ent->d_name, 0))
		{
			sb_free(sb);
			closedir(dir);
			return;
		}
		sb_append_char(sb, ' ');
		ent = readdir(dir);
	}
	closedir(dir);
	char *str = sb_build_str(sb);
	sn_printf("%s \n", str);
	free(str);
}
