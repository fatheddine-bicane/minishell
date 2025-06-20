/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:18:48 by fbicane           #+#    #+#             */
/*   Updated: 2025/06/16 19:07:00 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

void	sigint_handler(int signal)
{
	(void) signal;
	g_signal_flag = 9999;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	setup_signals(void)
{
	struct sigaction	signals;

	sigemptyset(&signals.sa_mask);
	signals.sa_flags = SA_RESTART;
	signals.sa_handler = sigint_handler;
	sigaction(SIGINT, &signals, NULL);
	signals.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &signals, NULL);
}

void	setup_signals_child(void)
{
	struct sigaction	signals;

	sigemptyset(&signals.sa_mask);
	signals.sa_flags = SA_RESTART;
	signals.sa_handler = SIG_DFL;
	sigaction(SIGINT, &signals, NULL);
	signals.sa_handler = SIG_DFL;
	sigaction(SIGQUIT, &signals, NULL);
}

void	ignore_signals_parrent(void)
{
	struct sigaction	signals;

	sigemptyset(&signals.sa_mask);
	signals.sa_flags = SA_RESTART;
	signals.sa_handler = SIG_IGN;
	sigaction(SIGINT, &signals, NULL);
	signals.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &signals, NULL);
}
