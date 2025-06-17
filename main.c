/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:21:00 by fbicane           #+#    #+#             */
/*   Updated: 2025/06/16 22:01:38 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

volatile sig_atomic_t	g_signal_flag = 0;

void	set_shell(t_shell *shell, int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	shell->exit_status = 0;
	shell->my_envp = ft_set_env(envp);
	shell->cmd = NULL;
	shell->heredocs_delemiters = NULL;
	shell->heredocs_files = NULL;
	shell->herdocs_index = 0;
	shell->is_group = false;
	std_files(SAVE);
	setup_signals();
}

bool	reset_shell(t_shell *shell)
{
	t_shell	shell_tmp;

	shell_tmp = (*shell);
	shell->is_pipe = false;
	shell->pids = NULL;
	shell->redirections_status = true;
	shell->pipex = NULL;
	shell->cmd = NULL;
	shell->heredocs_delemiters = NULL;
	shell->heredocs_files = NULL;
	shell->herdocs_index = 0;
	shell->is_group = false;
	g_signal_flag = 0;
	shell->prompt = custum_prompt(shell_tmp);
	shell->rl = readline(shell->prompt);
	free(shell->prompt);
	if (g_signal_flag == 9999)
		shell->exit_status = 130;
	if (rl_faild(shell))
		return (false);
	return (true);
}

bool	syntax_error(t_shell *shell)
{
	if (EXIT_SYNTAX_ERROR == shell->ast_status)
	{
		shell->exit_status = 2;
		free(shell->rl);
		return (true);
	}
	return (false);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	set_shell(&shell, argc, argv, envp);
	while (true)
	{
		if (false == reset_shell(&shell))
			continue ;
		shell.ast_status = create_ast(shell.rl, &shell.cmd);
		if (EXIT_EMPTY_AST != shell.ast_status)
		{
			add_history(shell.rl);
			if (syntax_error(&shell))
				continue ;
			if (NULL == shell.cmd)
				continue ;
			shell.root_to_free = shell.cmd;
			herdocs_delemiters(&shell);
			if (false == handle_herdocs(&shell) && clean_shell(&shell))
				continue ;
			run_ast(&shell);
			clean_shell(&shell);
			write(STDOUT_FILENO, "\n", 1);
		}
	}
	return (0);
}
