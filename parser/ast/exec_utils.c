/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/10/25 22:21:05 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

bool	append_lexeme(t_str_builder *sb, t_token *t)
{
	size_t	len;
	char	*str;
	size_t	total_size;
	int		str_size;

	if (t->type == T_WORD || t->type == T_STR_DOUBLE || t->type == T_STR_SINGLE
		|| t->type == T_VAR)
	{
		len = sb_len(sb);
		if (t->prev && t->prev->type != T_BLANK && len > 0)
		{
			str = NULL;
			total_size = sb->total_size - sn_strlen(sb->buff[len - 1]);
			str_size = sn_sprintf(&str, "%s%s", sb->buff[len - 1], t->lexeme);
			if (str_size == -1 || str == NULL)
				return (false);
			sb->total_size = total_size + str_size;
			free(sb->buff[len - 1]);
			sb->buff[len - 1] = str;
			return (true);
		}
	}
	return (sb_append_str(sb, t->lexeme, 0));
}

t_cmd	*append_redirect(t_cmd *root, t_cmd *new)
{
	t_cmd	*tmp;

	if (root == NULL)
		return (new);
	tmp = root;
	while (tmp->u_as.redirect.next)
		tmp = tmp->u_as.redirect.next;
	tmp->u_as.redirect.next = new;
	if (new)
		new->parent = tmp;
	return (root);
}

t_cmd	*combine_cmd(t_str_builder *sb, t_cmd *cmd)
{
	t_cmd	*tmp;

	if (cmd == NULL && sb_len(sb) > 0)
		return (cmd_exec_init(sb_build(sb), NULL));
	if (sb_len(sb) > 0)
	{
		tmp = cmd_exec_init(sb_build(sb), NULL);
		if (tmp == NULL)
			return (ast_free(cmd), NULL);
		append_redirect(cmd, tmp);
		sb = NULL;
	}
	return (sb_free(sb), cmd);
}
