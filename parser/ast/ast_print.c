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

static void	ast_walk(t_cmd *cmd, t_str_builder *sb, int depth);

void	cmp_print(t_cmd *cmd, t_str_builder *sb, int depth)
{
	char	*cmp_type;

	cmp_type = NULL;
	if (cmd->u_as.compound.type == T_AND)
		cmp_type = "and";
	if (cmd->u_as.compound.type == T_OR)
		cmp_type = "or";
	sb_append_char(sb, '(');
	sb_append_str(sb, cmp_type, 0);
	ast_walk(cmd->u_as.compound.left, sb, depth + 1);
	ast_walk(cmd->u_as.compound.right, sb, depth + 1);
	sb_append_char(sb, ')');
}

void	redirect_print(t_cmd *cmd, t_str_builder *sb, int depth)
{
	const char	*type;

	type = token_type_str(cmd->u_as.redirect.type);
	sb_append_str(sb, "(redirect(", 10);
	sb_append_str(sb, type, 0);
	sb_append_str(sb, ") ", 2);
	sb_append_str(sb, cmd->u_as.redirect.file, 0);
	if (cmd->u_as.redirect.next != NULL)
		ast_walk(cmd->u_as.redirect.next, sb, depth + 1);
	sb_append_char(sb, ')');
}

void	exec_print(t_cmd *cmd, t_str_builder *sb)
{
	char	**argv;

	sb_append_str(sb, "(exec ", 6);
	argv = cmd->u_as.exec.argv;
	while (*argv != NULL)
	{
		sb_append_str(sb, *argv++, 0);
		if (*argv)
			sb_append_char(sb, ' ');
	}
	sb_append_char(sb, ')');
}

static void	ast_walk(t_cmd *cmd, t_str_builder *sb, int depth)
{
	if (depth > 0)
		sb_append_char(sb, ' ');
	if (cmd == NULL)
		sb_append_str(sb, "empty", 5);
	if (cmd->type == C_EXEC)
		exec_print(cmd, sb);
	if (cmd->type == C_REDIRECT)
		redirect_print(cmd, sb, depth);
	if (cmd->type == C_GROUP)
	{
		sb_append_str(sb, "(subshell", 9);
		ast_walk(cmd->u_as.group.cmd, sb, depth + 1);
		sb_append_char(sb, ')');
	}
	if (cmd->type == C_PIPE)
	{
		sb_append_str(sb, "(pipe", 5);
		ast_walk(cmd->u_as.pipe.left, sb, depth + 1);
		ast_walk(cmd->u_as.pipe.right, sb, depth + 1);
		sb_append_char(sb, ')');
	}
	if (cmd->type == C_COMPOUND)
		cmp_print(cmd, sb, depth);
	if (depth == 0)
		sb_append_char(sb, '\n');
}

char	*ast_output(t_cmd *cmd, bool print)
{
	t_str_builder	*sb;
	char			*str;
	size_t			len;

	sb = sb_create(10);
	if (sb == NULL)
	{
		sn_eprintf("could not init string builder\n");
		exit(EXIT_FAILURE);
	}
	ast_walk(cmd, sb, 0);
	if (!print)
		sb_truncate(sb, sb_len(sb) - 1);
	len = sb_len(sb);
	str = sb_build(sb);
	if (str == NULL)
	{
		sn_eprintf("could not build string\n");
		exit(EXIT_FAILURE);
	}
	if (print)
		return (write(STDOUT_FILENO, str, len), free(str), NULL);
	return (str);
}
