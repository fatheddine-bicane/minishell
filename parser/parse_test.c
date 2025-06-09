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

volatile sig_atomic_t	g_sig;

void	catch_int(int sig)
{
	g_sig = sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

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

void	run_prompt(char *envp[])
{
	char	*line;

	(void)envp;
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

int	main(int argc, char *argv[], char *envp[])
{
	struct sigaction	sa;

	(void)argc;
	(void)argv;
	g_sig = 0;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = catch_int;
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
	run_prompt(envp);
	return (EXIT_SUCCESS);
}
