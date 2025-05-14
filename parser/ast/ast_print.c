/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/10/25 22:21:05 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

static void	ast_walk(t_cmd *cmd, int depth)
{
	char	**argv;

	if (depth > 0)
		printf(" ");
	if (cmd == NULL)
		printf("empty");
	if (cmd->type == C_EXEC)
	{
		printf("exec ");
		argv = cmd->u_as.exec.argv;
		while (*argv != NULL)
		{
			printf("%s", *argv++);
			if (*argv)
				printf(" ");
		}
	}
	if (cmd->type == C_REDIRECT)
	{
		// TODO:(karim) print string type of redirection
		printf("redirect(%d) %s", cmd->u_as.redirect.type,
			cmd->u_as.redirect.file);
		if (cmd->u_as.redirect.next != NULL)
			ast_walk(cmd->u_as.redirect.next, depth + 1);
	}
	if (cmd->type == C_GROUP)
	{
		printf("(group");
		ast_walk(cmd->u_as.group.cmd, depth + 1);
		printf(")");
	}
	if (cmd->type == C_PIPE)
	{
		printf("(|");
		ast_walk(cmd->u_as.pipe.left, depth + 1);
		ast_walk(cmd->u_as.pipe.right, depth + 1);
		printf(")");
	}
	if (depth == 0)
		printf("\n");
}

void	ast_print(t_cmd *cmd)
{
	ast_walk(cmd, 0);
}
