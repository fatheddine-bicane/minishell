/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sognals_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 19:06:45 by fbicane           #+#    #+#             */
/*   Updated: 2025/06/16 19:06:56 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

void	sigquit_heredoc_handler(int signal)
{
	(void) signal;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	setup_signals_heredoc(void)
{
	struct sigaction	signals;

	sigemptyset(&signals.sa_mask);
	signals.sa_flags = SA_RESTART;
	signals.sa_handler = SIG_DFL;
	sigaction(SIGINT, &signals, NULL);
	signals.sa_handler = sigquit_heredoc_handler;
	sigaction(SIGQUIT, &signals, NULL);
}
