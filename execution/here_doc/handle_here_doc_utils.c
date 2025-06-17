/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_here_doc_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 11:52:24 by fbicane           #+#    #+#             */
/*   Updated: 2025/06/16 12:46:29 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

bool	handle_herdocs(t_shell *shell)
{
	t_str_builder	*sb;
	int				i;
	char			*file_name;

	if (!shell->heredocs_delemiters)
		return (true);
	sb = sb_create(10);
	if (sb == NULL)
		return (true);
	shell->sb_to_free = sb;
	i = -1;
	while (shell->heredocs_delemiters[++i])
	{
		file_name = creat_here_doc(shell->heredocs_delemiters[i], shell);
		if (NULL == file_name)
		{
			sb_append_str(sb, file_name, 0);
			shell->heredocs_files = sb_build(sb);
			return (ft_free_arr(shell->heredocs_delemiters), false);
		}
		sb_append_str(sb, file_name, 0);
		free (file_name);
	}
	shell->heredocs_files = sb_build(sb);
	return (ft_free_arr(shell->heredocs_delemiters), true);
}
