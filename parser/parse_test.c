/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/10/25 22:21:05 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	run(char *src)
{
	t_cmd	*ast;
	int		status;

	ast = NULL;
	status = create_ast(src, &ast);
	if (status != EXIT_EMPTY_AST && status != EXIT_SYNTAX_ERROR)
		ast_output(ast, true);
	return (ast_free(ast), status);
}

void	run_prompt(void)
{
	char	*line;

	while (1)
	{
		line = readline("shell> ");
		if (line == NULL)
		{
			write(STDOUT_FILENO, "exit\n", 5);
			rl_clear_history();
			break ;
		}
		if (*line)
		{
			if (run(line) != EXIT_EMPTY_AST)
				add_history(line);
		}
		free(line);
	}
}

int	main(void)
{
	run_prompt();
	return (EXIT_SUCCESS);
}
