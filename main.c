/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:21:00 by fbicane           #+#    #+#             */
/*   Updated: 2025/05/20 14:34:15 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

/*t_data create_data()*/
/*{*/
/*	static t_data data;*/
/**/
/*	data.dsdsa = 232;*/
/*	return data;*/
/*}*/

void	sigint_handler(int signal)
{
	if (SIGINT == signal)
	{
		g_signal_flag = SIGINT;
		rl_on_new_line();
		/*rl_replace_line("", 0);*/
		rl_redisplay();
	}
}

void	ft_setup_signals(void)
{
	struct sigaction signals;

	signals.sa_handler = sigint_handler;
	sigemptyset(&signals.sa_mask);
	signals.sa_flags = SA_RESTART;
	sigaction(SIGINT, &signals, NULL);
}

int main(int argc, char **argv, char **envp)
{
	t_list *my_envp;

	(void)argc;
	(void)argv;

	my_envp = ft_set_env(envp);
	ft_setup_signals();
	while (1)
	{
		g_signal_flag = 0;
		char (*rl) = readline("====> ");
		if (SIGINT == g_signal_flag)
		{
			free (rl);
			continue;
		}
		/*rl = readline("╭─ minishell \n╰─> ");*/
		// BUG: if an empty line is set to rl there is segfault

		// INFO: to test pipes
		/*ft_pipex(ft_split(rl, '|'), &my_envp);*/
		/*continue;*/

		if (ft_check_bultins(rl, &my_envp))
		{
			continue ;
			add_history(rl);
		}

		/*ft_here_doc(rl);*/
		ft_apply_comm(rl, my_envp);

		/*if (errno != 0)*/
		/*	perror(strerror(errno));*/

		add_history(rl);
		printf("\n");
	}
    return (0);
}
