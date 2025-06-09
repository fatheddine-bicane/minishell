/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_core.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/10/25 22:21:05 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

t_cmd	*parse_program(t_token **token, int *status);

int	create_ast(char *src, t_cmd **ast)
{
	t_token	*tokens;
	t_token	*head;
	char	*lexeme;
	int		status;

	status = 0;
	tokens = tokens_scan(src);
	if (tokens == NULL)
		return (EXIT_SYNTAX_ERROR);
	if (is_end(tokens))
		return (tokens_free(tokens), EXIT_EMPTY_AST);
	head = tokens;
	*ast = parse_program(&tokens, &status);
	if (*ast == NULL || !is_end(tokens))
	{
		lexeme = extract_lexeme_err(tokens);
		sn_eprintf("syntax error near unexpected token `%s`\n", lexeme);
		ast_free(*ast);
		*ast = NULL;
		return (tokens_free(head), EXIT_SYNTAX_ERROR);
	}
	return (tokens_free(head), EXIT_SUCCESS);
}

void	ast_free(t_cmd *root)
{
	if (root == NULL)
		return ;
	if (root->type == C_EXEC)
		(sn_strs_free(root->u_as.exec.argv), free(root));
	else if (root->type == C_COMPOUND)
	{
		ast_free(root->u_as.compound.left);
		ast_free(root->u_as.compound.right);
		free(root);
	}
	else if (root->type == C_PIPE)
	{
		ast_free(root->u_as.pipe.left);
		ast_free(root->u_as.pipe.right);
		free(root);
	}
	else if (root->type == C_REDIRECT)
	{
		if (root->u_as.redirect.next != NULL)
			ast_free(root->u_as.redirect.next);
		free(root->u_as.redirect.file);
		free(root);
	}
	else if (root->type == C_GROUP)
		(ast_free(root->u_as.group.cmd), free(root));
}
