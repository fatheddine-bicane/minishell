/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/10/25 22:21:05 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

t_cmd	*parse_program(t_token **token, int *status);

char	*ast_gen(char *src)
{
	t_token	*tokens;
	t_token	*head;
	t_cmd	*ast;
	char	*got;
	int		status;

	tokens = tokens_scan(src);
	head = tokens;
	status = 0;
	ast = parse_program(&tokens, &status);
	got = ast_output(ast, false);
	return (tokens_free(head), ast_free(ast), got);
}
