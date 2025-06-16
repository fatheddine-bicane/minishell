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

void set_shell(t_shell *shell, int argc, char **argv, char **envp)
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
}

void reset_shell(t_shell *shell)
{
	shell->is_pipe = false;
	shell->pids = NULL;
	shell->redirections_status = true;
	shell->pipex = NULL;
	shell->cmd = NULL;
	shell->heredocs_delemiters = NULL;
	shell->heredocs_files = NULL;
	shell->herdocs_index = 0;
	shell->is_group = false;
}

int main(int argc, char **argv, char **envp)
{
	t_shell shell;

	set_shell(&shell, argc, argv, envp);
	std_files(SAVE);
	setup_signals();
	while (true)
	{
		reset_shell(&shell);
		g_signal_flag = 0;
		shell.prompt = custum_prompt(shell);
		shell.rl = readline(shell.prompt);
		free(shell.prompt);
		if (rl_faild(&shell))
			continue ;
		shell.ast_status = create_ast(shell.rl, &shell.cmd);
		if (shell.ast_status != EXIT_EMPTY_AST)
		{
			add_history(shell.rl);
			if (EXIT_SYNTAX_ERROR == shell.ast_status)
			{
				shell.exit_status = 2;
				continue ;
			}
			if (shell.cmd == NULL)
				continue;
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

