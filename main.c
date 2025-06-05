/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:21:00 by fbicane           #+#    #+#             */
/*   Updated: 2025/06/05 13:14:14 by fbicane          ###   ########.fr       */
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

int main(int argc, char **argv, char **envp)
{
	/*t_list *my_envp;*/
	t_cmd	*cmd;
	/*int		exit_stat = 0;*/



	t_shell shell;

	shell.exit_status = 0;
	shell.my_envp = ft_set_env(envp);

	(void)argc;
	(void)argv;

	/*my_envp = ft_set_env(envp);*/
	setup_signals();
	cmd = NULL;
	printf("PID: %d\n", getpid());
	std_files(SAVE);
	while (true)
	{

		ft_putstr_fd("new prompt is coming\n",2);
		shell.is_pipe = false;
		shell.pids = NULL;
		shell.pipe = NULL;
		shell.redirections_status = true;
		shell.pipex = NULL;

		/*shell.c_exec = NULL;*/
		/*shell.c_redirect = NULL;*/
		/*shell.c_pipe = NULL;*/
		/*shell.c_group = NULL;*/
		/*shell.c_compound = NULL;*/
		g_signal_flag = 0;


		char (*rl) = readline("====> ");
		if (!rl)
		{
			write(STDOUT_FILENO, "exit\n", 5);
			free_my_envp(&shell.my_envp);
			exit(shell.exit_status); // INFO: bash exits with the last exit status
		}
		if (*rl == '\0')
			continue;




		if (create_ast(rl, &cmd) != EXIT_EMPTY_AST) // INFO: return status 
		{
			add_history(rl);
			if (cmd == NULL)
				continue; // INFO: syntax error



			shell.cmd = cmd;
			shell.root_to_free = cmd;

			if (cmd->type == C_EXEC)
			{
				/*is_command(cmd, &my_envp, &exit_stat);*/
				is_command(&shell, true, -3);
			}
			else if (cmd->type == C_REDIRECT)
			{
				is_redirection(&shell, true, -3);
				// if (!shell.redirections_status)
				// 	shell.redirections_status = true;
			}
			else if (cmd->type == C_PIPE)
			{
				is_pipe(&shell);
			}
			else if (C_GROUP == cmd->type)
			{
				is_group(&shell);
			}
			else if (C_COMPOUND == cmd->type)
			{
				is_compound(&shell);
			}
			else
				printf("not a command\n");
			ast_free(cmd);
		}
	}
    return (0);
}
