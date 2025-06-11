/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:21:00 by fbicane           #+#    #+#             */
/*   Updated: 2025/06/11 23:27:48 by fbicane          ###   ########.fr       */
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
}

void reset_shell(t_shell *shell)
{
	shell->is_pipe = false;
	shell->pids = NULL;
	shell->pipe = NULL; // TODO: eleminate
	shell->redirections_status = true;
	shell->pipex = NULL;
	shell->cmd = NULL;
	shell->heredocs_delemiters = NULL;
	shell->heredocs_files = NULL;
	shell->herdocs_index = 0;
}

void	unlink_files(t_shell *shell)
{
	int	i;

	if (NULL == shell->heredocs_files)
		return ;
	i = 0;
	while (shell->heredocs_files[i])
	{
		unlink(shell->heredocs_files[i]);
		i++;
	}
	ft_free_arr(shell->heredocs_files);
	shell->heredocs_files = NULL;
}

int main(int argc, char **argv, char **envp)
{
	t_shell shell;
	char *rl;
	/*t_list *my_envp;*/
	/*t_cmd	*cmd;*/
	/*int		exit_stat = 0;*/

	/*shell.exit_status = 0;*/
	/*shell.my_envp = ft_set_env(envp);*/
	/**/
	/*(void)argc;*/
	/*(void)argv;*/

	/*my_envp = ft_set_env(envp);*/
	/*cmd = NULL;*/
	/*shell.cmd = NULL;*/

	set_shell(&shell, argc, argv, envp);
	std_files(SAVE);
	setup_signals();
	while (true)
	{

		reset_shell(&shell);
		g_signal_flag = 0;

		char *prompt = custum_prompt(shell);
		rl = readline(prompt);
		free(prompt);
		if (!rl)
		{
			write(STDOUT_FILENO, "exit\n", 5);
			free_my_envp(&shell.my_envp);
			exit(shell.exit_status); // INFO: bash exits with the last exit status
		}
		if (*rl == '\0')
		{
			write(STDOUT_FILENO, "\n", 1);
			continue;
		}

		if (create_ast(rl, &shell.cmd) != EXIT_EMPTY_AST) // INFO: return status
		{
			add_history(rl);
			if (shell.cmd == NULL)
				continue; // INFO: syntax error

			/*shell.cmd = cmd;*/
			shell.root_to_free = shell.cmd;
			
			ast_output(shell.cmd, true);
			write(1, "\n", 1);

			herdocs_delemiters(&shell);
			handle_herdocs(&shell);
			if (shell.cmd->type == C_EXEC)
			{
				/*is_command(cmd, &my_envp, &exit_stat);*/
				is_command(&shell, true, -3);
			}
			else if (shell.cmd->type == C_REDIRECT)
			{
				is_redirection(&shell, true, -3);
				// if (!shell.redirections_status)
				// 	shell.redirections_status = true;
			}
			else if (shell.cmd->type == C_PIPE)
			{
				is_pipe(&shell);
			}
			else if (C_GROUP == shell.cmd->type)
			{
				is_group(&shell);
			}
			else if (C_COMPOUND == shell.cmd->type)
			{
				is_compound(&shell);
			}
			else
				printf("not a command\n");
			unlink_files(&shell);
			ft_free_arr(shell.heredocs_files);
			ast_free(shell.root_to_free);
			write(STDOUT_FILENO, "\n", 1);
		}
	}
	return (0);
}
