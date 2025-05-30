/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:21:00 by fbicane           #+#    #+#             */
/*   Updated: 2025/05/29 16:52:56 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"
#include "parser/parser.h"
#include <stdio.h>

/*t_data create_data()*/
/*{*/
/*	static t_data data;*/
/**/
/*	data.dsdsa = 232;*/
/*	return data;*/
/*}*/

/*int	run(char *src)*/
/*{*/
/*	t_cmd	*ast;*/
/*	int		status;*/
/**/
/*	ast = NULL;*/
/*	status = create_ast(src, &ast);*/
/*	if (status != EXIT_EMPTY_AST && status != EXIT_SYNTAX_ERROR)*/
/*		ast_output(ast, true);*/
/*	return (ast_free(ast), status);*/
/*}*/


int main(int argc, char **argv, char **envp)
{
	t_list *my_envp;
	t_cmd	*cmd;
	int		exit_stat = 0;


	(void)argc;
	(void)argv;

	my_envp = ft_set_env(envp);
	setup_signals();
	cmd = NULL;
	while (1)
	{
		// TODO: maybe update the exit status here (use global variable)
		g_signal_flag = 0;
		char (*rl) = readline("====> ");
		if (!rl)
		{
			write(STDOUT_FILENO, "exit\n", 5);
			break ;
		}

		if (*rl == '\0')
			continue;
		if (create_ast(rl, &cmd) != EXIT_EMPTY_AST) // INFO: return status 
		{
			add_history(rl);
			if (cmd == NULL)
				continue; // INFO: syntax error
			if (cmd->type == C_EXEC)
			{
				is_command(cmd, &my_envp, &exit_stat);
			}
			else if (cmd->type == C_REDIRECT)
			{
				is_redirection(cmd, &my_envp, &exit_stat);
			}
			else
				printf("not a command\n");
			ast_free(cmd);

		}

		/*rl = readline("╭─ minishell \n╰─> ");*/
		// BUG: if an empty line is set to rl there is segfault

		// INFO: to test pipes
		/*ft_pipex(ft_split(rl, '|'), &my_envp);*/
		/*continue;*/


		/*ft_here_doc(rl);*/
		// ft_apply_comm(rl, my_envp);

		/*if (errno != 0)*/
		/*	perror(strerror(errno));*/

	}
    return (0);
}

/*int main(int argc, char **argv, char **envp)*/
/*{*/
/*	t_list	*my_envp;*/
/*	int		exit_stat = 0;*/
/**/
/*	(void)argc;*/
/*	(void)argv;*/
/**/
/*	my_envp = ft_set_env(envp);*/
/*	setup_signals();*/
/*	while (1)*/
/*	{*/
/*		// TODO: maybe update the exit status here (use global variable)*/
/*		g_signal_flag = 0;*/
/*		char (*rl) = readline("====> ");*/
/*		if (!rl)*/
/*		{*/
/*			write(STDOUT_FILENO, "exit\n", 5);*/
/*			break ;*/
/*		}*/
		/*rl = readline("╭─ minishell \n╰─> ");*/
/*		// BUG: if an empty line is set to rl there is segfault*/
/**/
/*		// INFO: to test pipes*/
		/*ft_pipex(ft_split(rl, '|'), &my_envp, &exit_stat);*/
		/*continue;*/
/**/
		/*if (ft_is_builtin(argv))*/
/*		if (run_bultins(ft_split(rl, 32), &my_envp, &exit_stat))*/
/*		{*/
/*			continue ;*/
/*			add_history(rl);*/
/*		}*/
/**/
		/*ft_here_doc(rl);*/
/*		ft_apply_comm(rl, my_envp, &exit_stat);*/
/**/
		/*if (errno != 0)*/
		/*	perror(strerror(errno));*/
/**/
/*		add_history(rl);*/
/*	}*/
/*	return (0);*/
/*}*/
