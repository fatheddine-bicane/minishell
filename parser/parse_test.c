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
			rl_clear_history();
			printf("exit\n");
			break ;
		}
		run(line);
		if (*line)
			add_history(line);
		free(line);
	}
}

int	main(void)
{
	run_prompt();
	return (EXIT_SUCCESS);
}
