/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 21:37:37 by fbicane           #+#    #+#             */
/*   Updated: 2025/05/29 16:20:47 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

// INFO: to call before handling redirections mainly if executing a builtin
void	save_std_files(bool save)
{
	static int	std_in_save;
	static int	std_out_save;

	if (true == save)
	{
		std_in_save = dup(STDIN_FILENO);
		if (-1 == std_in_save)
			return ; // TODO: error mssg
		int	std_out_save = dup(STDOUT_FILENO);
		if (-1 == std_out_save)
			return ; // TODO: error mssg
	}
	else
	{
		dup2(std_in_save, STDIN_FILENO);
		dup2(std_out_save, STDOUT_FILENO);
	}
}

/*void	run_bultins(char **argv, t_list **my_envp, int *exit_stat)*/
void	run_bultins(t_shell *shell)
{
	if (!ft_strncmp("unset", shell->cmd->u_as.exec.argv[0], 5))
	{
		ft_unset(shell);
	}
	else if (!ft_strncmp("cd", shell->cmd->u_as.exec.argv[0], 2))
	{
		ft_cd(shell);
	}
	else if (!ft_strncmp("pwd", shell->cmd->u_as.exec.argv[0], 3))
	{
		ft_pwd(shell);
	}
	else if (!ft_strncmp("env", shell->cmd->u_as.exec.argv[0], 3))
	{
		ft_env(shell);
	}
	else if (!ft_strncmp("echo", shell->cmd->u_as.exec.argv[0], 4))
	{
		ft_echo(shell);
	}
	else if (!ft_strncmp("exit", shell->cmd->u_as.exec.argv[0], 4))
	{
		ft_exit(shell);
	}
	else if (!ft_strncmp("export", shell->cmd->u_as.exec.argv[0], 6))
	{
		ft_export(shell);
	}
	/*ft_free_arr(argv);*/
}
