/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:21:00 by fbicane           #+#    #+#             */
/*   Updated: 2025/05/23 17:21:09 by fbicane          ###   ########.fr       */
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

/*int	run(char *src, t_cmd **cmd)*/
/*{*/
/*	t_token	*tokens;*/
/*	t_token	*head;*/
/*	char	*lexeme;*/
/**/
/*	tokens = tokens_scan(src);*/
/*	if (tokens == NULL)*/
/*		return (EX_DATAERR);*/
/*	if (is_end(tokens))*/
/*		return (tokens_free(tokens), EXIT_EMPTY_AST);*/
/*	head = tokens;*/
/*	*cmd = parse_program(&tokens);*/
/*	if (cmd == NULL || !is_end(tokens))*/
/*	{*/
/*		lexeme = extract_lexeme_err(tokens);*/
/*		sn_eprintf("syntax error near unexpected token `%s`\n", lexeme);*/
/*		return (ast_free(*cmd), tokens_free(head), EXIT_FAILURE);*/
/*	}*/
/*	tokens_free(head);*/
/*	return (EXIT_SUCCESS);*/
/*}*/

/*int main(int argc, char **argv, char **envp)*/
/*{*/
/*	t_list *my_envp;*/
/*	t_cmd	*cmd;*/
/**/
/**/
/*	(void)argc;*/
/*	(void)argv;*/
/**/
/*	my_envp = ft_set_env(envp);*/
/*	setup_signals();*/
/*	cmd = NULL;*/
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
/**/
/*		if (*rl == '\0')*/
/*			continue;*/
/*		if (run(rl, &cmd) != EXIT_EMPTY_AST)*/
/*		{*/
/*			add_history(rl);*/
/*			if (cmd == NULL)*/
/*				continue;*/
/*			if (cmd->type == C_EXEC)*/
/*			{*/
/*				if (ft_check_bultins(cmd->u_as.exec.argv, &my_envp))*/
/*				{*/
/*					continue ;*/
/*				}*/
/*			}*/
/*			ast_free(cmd);*/
/**/
/*		}*/
/**/
		/*rl = readline("╭─ minishell \n╰─> ");*/
/*		// BUG: if an empty line is set to rl there is segfault*/
/**/
/*		// INFO: to test pipes*/
		/*ft_pipex(ft_split(rl, '|'), &my_envp);*/
		/*continue;*/
/**/
/**/
		/*ft_here_doc(rl);*/
/*		// ft_apply_comm(rl, my_envp);*/
/**/
		/*if (errno != 0)*/
		/*	perror(strerror(errno));*/
/**/
/*	}*/
/*    return (0);*/
/*}*/

int main(int argc, char **argv, char **envp)
{
	t_list	*my_envp;
	int		exit_stat = 0;

	(void)argc;
	(void)argv;

	my_envp = ft_set_env(envp);
	setup_signals();
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
		/*rl = readline("╭─ minishell \n╰─> ");*/
		// BUG: if an empty line is set to rl there is segfault

		// INFO: to test pipes
		/*ft_pipex(ft_split(rl, '|'), &my_envp);*/
		/*continue;*/

		if (ft_check_bultins(rl, &my_envp, &exit_stat))
		{
			continue ;
			add_history(rl);
		}

		/*ft_here_doc(rl);*/
		ft_apply_comm(rl, my_envp, &exit_stat);

		/*if (errno != 0)*/
		/*	perror(strerror(errno));*/

		add_history(rl);
	}
	return (0);
}
