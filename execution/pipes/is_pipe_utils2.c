/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_pipe_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:43:48 by fbicane           #+#    #+#             */
/*   Updated: 2025/06/16 14:39:18 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

t_pipex	*new_cmd_(t_cmd *cmd)
{
	t_pipex	*res;

	res = (t_pipex *)malloc(sizeof(t_pipex));
	if (!res)
		return (NULL);
	res->cmd = cmd;
	res->next = NULL;
	return (res);
}

void	append_cmd_(t_pipex **pipex, t_cmd *cmd)
{
	t_pipex	*tmp;

	if (!(*pipex))
		(*pipex) = new_cmd_(cmd);
	else
	{
		tmp = (*pipex);
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_cmd_(cmd);
	}
}

void	creat_pipex(t_cmd *cmd, t_pipex **pipex)
{
	if (C_PIPE == cmd->type)
		creat_pipex(cmd->u_as.pipe.left, pipex);
	if (C_EXEC == cmd->type || C_REDIRECT == cmd->type || C_GROUP == cmd->type)
		append_cmd_(pipex, cmd);
	if (C_PIPE == cmd->type)
		append_cmd_(pipex, cmd->u_as.pipe.right);
}

void	free_pipex(t_pipex **pipex)
{
	t_pipex	*tmp;
	t_pipex	*to_free;

	if (!pipex || !*pipex)
		return ;
	tmp = (*pipex);
	while (tmp)
	{
		to_free = tmp;
		tmp = tmp->next;
		free(to_free);
	}
	(*pipex) = NULL;
}

void	increment_heredoc_pipe(t_shell *shell, t_pipex *tmp)
{
	if (C_REDIRECT == tmp->cmd->type)
	{
		while (tmp->cmd)
		{
			if (C_REDIRECT != tmp->cmd->type)
				break ;
			if (T_HEREDOC == tmp->cmd->u_as.redirect.type)
				shell->herdocs_index++;
			tmp->cmd = tmp->cmd->u_as.redirect.next;
		}
	}
	else if (C_GROUP == tmp->cmd->type)
	{
		tmp->cmd = tmp->cmd->u_as.group.cmd;
		increment_heredoc_pipe(shell, tmp);
	}
}
