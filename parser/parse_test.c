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
	t_token	*tokens;

	tokens = tokens_scan(src);
	if (tokens == NULL)
		return (EX_DATAERR);
	token_str(tokens, true, true);
	return (token_free(tokens), EXIT_SUCCESS);
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
			add_history(line);
			run(line);
		}
		free(line);
	}
}

int	main(void)
{
	struct sigaction	sa;

	g_sig = 0;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = catch_int;
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
	run_prompt();
	return (EXIT_SUCCESS);
}
