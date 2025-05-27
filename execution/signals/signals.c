/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:18:48 by fbicane           #+#    #+#             */
/*   Updated: 2025/05/21 10:33:46 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

void	sigint_handler(int signal)
{
	(void) signal;
	g_signal_flag = SIGINT;
	write(STDOUT_FILENO, "\n", 1);
	/*rl_replace_line("", 0);*/
	write(STDOUT_FILENO, "====> ", 6); // PERF: rl_replace_line() not available on mac
	rl_on_new_line();
	rl_redisplay();
}

void	setup_signals(void)
{
	struct sigaction signals;

	signals.sa_handler = sigint_handler;
	sigemptyset(&signals.sa_mask);
	signals.sa_flags = SA_RESTART;
	sigaction(SIGINT, &signals, NULL);
	signals.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &signals, NULL);
	/*signal(SIGINT, sigint_handler);*/
}

void	ignore_signals_parrent(void)
{
	struct sigaction	signal;

	sigemptyset(&signal.sa_mask);
	signal.sa_flags = SA_RESTART;
	signal.sa_handler = SIG_IGN;
	sigaction(SIGINT, &signal, NULL);
	signal.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &signal, NULL);
}
