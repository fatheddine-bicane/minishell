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

char	*ast_gen(char *src)
{
	t_token	*tokens;
	t_token	*head;
	t_cmd	*ast;
	char	*got;

	tokens = tokens_scan(src);
	head = tokens;
	ast = parse_program(&tokens);
	got = ast_output(ast, false);
	return (tokens_free(head), ast_free(ast), got);
}
