/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 21:30:05 by fbicane           #+#    #+#             */
/*   Updated: 2025/06/16 23:53:23 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

static void unlink_files(t_shell *shell)
{
	int i;

	if (NULL == shell->heredocs_files)
		return;
	i = 0;
	while (shell->heredocs_files[i])
	{
		unlink(shell->heredocs_files[i]);
		i++;
	}
	ft_free_arr(shell->heredocs_files);
	shell->heredocs_files = NULL;
}

int	clean_shell(t_shell *shell)
{
	unlink_files(shell);
	ast_free(shell->root_to_free);
	ft_free_arr(shell->heredocs_files);
	return (1);
}

bool	rl_faild(t_shell *shell)
{
	if (NULL == shell->rl)
	{
		ft_printf("exit\n");
		free_my_envp(&shell->my_envp);
		exit(shell->exit_status);
	}
	if ('\0' == shell->rl[0])
	{
		write(STDOUT_FILENO, "\n", 1);
		return (true);
	}
	return (false);
}

void	run_ast(t_shell *shell)
{
	if (shell->cmd->type == C_EXEC)
	{
		is_command(shell, true, -3);
	}
	else if (shell->cmd->type == C_REDIRECT)
	{
		is_redirection(shell, true, -3);
	}
	else if (shell->cmd->type == C_PIPE)
	{
		is_pipe(shell);
	}
	else if (C_GROUP == shell->cmd->type)
	{
		is_group(shell);
	}
	else if (C_COMPOUND == shell->cmd->type)
	{
		is_compound(shell);
	}
}
