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

static void	ast_walk(t_cmd *cmd, int depth);

void	cmp_print(t_cmd *cmd, int depth)
{
	char	*cmp_type;

	cmp_type = NULL;
	if (cmd->u_as.compound.type == OP_AND)
		cmp_type = "and";
	if (cmd->u_as.compound.type == OP_OR)
		cmp_type = "or";
	printf("(%s", cmp_type);
	ast_walk(cmd->u_as.compound.left, depth + 1);
	ast_walk(cmd->u_as.compound.right, depth + 1);
	printf(")");
}

// TODO:(karim) print string type of redirection
void	redirect_print(t_cmd *cmd, int depth)
{
	printf("(redirect(%d) %s", cmd->u_as.redirect.type,
		cmd->u_as.redirect.file);
	if (cmd->u_as.redirect.next != NULL)
		ast_walk(cmd->u_as.redirect.next, depth + 1);
	printf(")");
}

void	exec_print(t_cmd *cmd)
{
	char	**argv;

	printf("(exec ");
	argv = cmd->u_as.exec.argv;
	while (*argv != NULL)
	{
		printf("%s", *argv++);
		if (*argv)
			printf(" ");
	}
	printf(")");
}

static void	ast_walk(t_cmd *cmd, int depth)
{
	if (depth > 0)
		printf(" ");
	if (cmd == NULL)
		printf("empty");
	if (cmd->type == C_EXEC)
		exec_print(cmd);
	if (cmd->type == C_REDIRECT)
		redirect_print(cmd, depth);
	if (cmd->type == C_GROUP)
	{
		printf("(subshell");
		ast_walk(cmd->u_as.group.cmd, depth + 1);
		printf(")");
	}
	if (cmd->type == C_PIPE)
	{
		printf("(pipe");
		ast_walk(cmd->u_as.pipe.left, depth + 1);
		ast_walk(cmd->u_as.pipe.right, depth + 1);
		printf(")");
	}
	if (cmd->type == C_COMPOUND)
		cmp_print(cmd, depth);
	if (depth == 0)
		printf("\n");
}

void	ast_print(t_cmd *cmd)
{
	ast_walk(cmd, 0);
}
