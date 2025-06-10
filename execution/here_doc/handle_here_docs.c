/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_here_docs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:19:34 by fbicane           #+#    #+#             */
/*   Updated: 2025/06/10 13:47:51 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

void	creat_heredoc_command(t_shell *shell, t_str_builder **sb)
{
	t_cmd	*tmp_cmd;

	tmp_cmd = shell->cmd;
	while (tmp_cmd)
	{
		if (C_REDIRECT != tmp_cmd->type)
			break;
		if (T_HEREDOC == tmp_cmd->u_as.redirect.type)
			sb_append_str((*sb), tmp_cmd->u_as.redirect.file, 0);
		tmp_cmd = tmp_cmd->u_as.redirect.next;
	}
}

void	creat_heredoc_pipe(t_shell *shell, t_str_builder **sb)
{
	t_pipex *pipex;
	t_pipex *pipex_to_free;

	pipex = NULL;
	creat_pipex(shell->cmd, &pipex);
	pipex_to_free = pipex;
	while (pipex)
	{
		shell->cmd = pipex->cmd;
		creat_heredoc_command(shell, sb);
		pipex = pipex->next;
	}
	free_pipex(&pipex_to_free);
}

void	creat_heredocs(t_shell *shell)
{
	char **str;
	t_str_builder	*sb;

	sb = sb_create(10);
	if (sb == NULL)
		return ;
	if (C_REDIRECT == shell->cmd->type)
	{
		creat_heredoc_command(shell, &sb);
	}
	else if (C_PIPE == shell->cmd->type)
	{
		creat_heredoc_pipe(shell, &sb);
	}

	str = sb_build(sb);
	if (NULL == str)
	{
		shell->cmd = shell->root_to_free;
		return (ft_putstr_fd("no heredocs\n", 2));
	}

	for (int i = 0; str[i]; i++)
		printf("delimiter[%s]\n", str[i]);
	shell->cmd = shell->root_to_free;
	ft_free_arr(str);
}
