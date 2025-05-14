/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/10/25 22:21:05 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

t_cmd	*cmd_exec_init(char **argv)
{
	t_cmd	*cmd;

	if (argv == NULL || *argv == NULL)
		return (NULL);
	cmd = malloc(sizeof(t_cmd));
	if (cmd == NULL)
		return (NULL);
	cmd->type = C_EXEC;
	cmd->u_as.exec.argv = argv;
	return (cmd);
}

t_cmd	*cmd_redirect_init(t_redirect_type type, char *file, t_cmd *next)
{
	t_cmd	*cmd;

	if (file == NULL)
		return (NULL);
	cmd = malloc(sizeof(t_cmd));
	if (cmd == NULL)
		return (NULL);
	cmd->type = C_REDIRECT;
	cmd->u_as.redirect.type = type;
	cmd->u_as.redirect.file = file;
	cmd->u_as.redirect.next = next;
	return (cmd);
}

t_cmd	*cmd_pipe_init(t_cmd *left, t_cmd *right)
{
	t_cmd	*cmd;

	if (left == NULL || right == NULL)
		return (NULL);
	cmd = malloc(sizeof(t_cmd));
	if (cmd == NULL)
		return (NULL);
	cmd->type = C_PIPE;
	cmd->u_as.pipe.left = left;
	cmd->u_as.pipe.right = right;
	return (cmd);
}

t_cmd	*cmd_group_init(t_cmd *group)
{
	t_cmd	*cmd;

	if (group == NULL)
		return (NULL);
	cmd = malloc(sizeof(t_cmd));
	if (cmd == NULL)
		return (NULL);
	cmd->type = C_GROUP;
	cmd->u_as.group.cmd = group;
	return (cmd);
}

void	cmd_free(t_cmd *root)
{
	if (root == NULL)
		return ;
	if (root->type == C_EXEC)
	{
		sn_split_free(root->u_as.exec.argv);
		free(root);
	}
	else if (root->type == C_PIPE)
	{
		cmd_free(root->u_as.pipe.left);
		cmd_free(root->u_as.pipe.right);
		free(root);
	}
	else if (root->type == C_REDIRECT)
	{
		if (root->u_as.redirect.next != NULL)
			cmd_free(root->u_as.redirect.next);
		free(root->u_as.redirect.file);
		free(root);
	}
	else if (root->type == C_GROUP)
	{
		cmd_free(root->u_as.group.cmd);
		free(root);
	}
}
