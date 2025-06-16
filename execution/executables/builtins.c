/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 21:37:37 by fbicane           #+#    #+#             */
/*   Updated: 2025/06/05 13:09:05 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

void	save_std_files(bool save)
{
	static int	std_in_save;
	static int	std_out_save;

	if (true == save)
	{
		std_in_save = dup(STDIN_FILENO);
		if (-1 == std_in_save)
			return (perror("dup()"));
		std_out_save = dup(STDOUT_FILENO);
		if (-1 == std_out_save)
			return (perror("dup()"));
	}
	else
	{
		dup2(std_in_save, STDIN_FILENO);
		dup2(std_out_save, STDOUT_FILENO);
	}
}

static void	free_heredocs_files(t_shell *shell)
{
	if (shell->is_pipe || shell->is_group)
	{
		if (NULL != shell->heredocs_files)
		{
			ft_free_arr(shell->heredocs_files);
			shell->heredocs_files = NULL;
		}
	}
}

void	run_bultins_utils(t_shell *shell)
{
	if (!ft_strncmp("env", shell->cmd->u_as.exec.argv[0], 3))
	{
		ft_env(shell);
		free_heredocs_files(shell);
	}
	else if (!ft_strncmp("echo", shell->cmd->u_as.exec.argv[0], 4))
	{
		ft_echo(shell);
		free_heredocs_files(shell);
	}
	else if (!ft_strncmp("exit", shell->cmd->u_as.exec.argv[0], 4))
	{
		ft_exit(shell);
		free_heredocs_files(shell);
	}
	else if (!ft_strncmp("export", shell->cmd->u_as.exec.argv[0], 6))
	{
		ft_export(shell);
		free_heredocs_files(shell);
	}
}

void	run_bultins(t_shell *shell)
{
	if (!ft_strncmp("unset", shell->cmd->u_as.exec.argv[0], 5))
	{
		ft_unset(shell);
		free_heredocs_files(shell);
	}
	else if (!ft_strncmp("cd", shell->cmd->u_as.exec.argv[0], 2))
	{
		ft_cd(shell);
		free_heredocs_files(shell);
	}
	else if (!ft_strncmp("pwd", shell->cmd->u_as.exec.argv[0], 3))
	{
		ft_pwd(shell);
		free_heredocs_files(shell);
	}
	else
		run_bultins_utils(shell);
}
