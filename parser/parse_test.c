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

int	run(char *src, char **envp)
{
	t_token	*tokens;
	t_token	*head;
	t_cmd	*cmd;
	char	*lexeme;

	(void)envp;
	tokens = tokens_scan(src);
	if (tokens == NULL)
		return (EX_DATAERR);
	if (is_end(tokens))
		return (tokens_free(tokens), EXIT_EMPTY_AST);
	head = tokens;
	cmd = parse_program(&tokens);
	if (cmd == NULL)
		return (tokens_free(head), EXIT_SYNTAX_ERROR);
	if (tokens->type != T_EOF || (tokens->type == T_BLANK
			&& tokens->next->type != T_EOF))
	{
		lexeme = extract_lexeme_err(tokens);
		sn_eprintf("syntax error near unexpected token `%s`\n", lexeme);
		return (EXIT_FAILURE);
	}
	ast_print(cmd);
	return (ast_free(cmd), tokens_free(head), EXIT_SUCCESS);
}

void	run_prompt(char *envp[])
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
			if (run(line, envp) != EXIT_EMPTY_AST)
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
