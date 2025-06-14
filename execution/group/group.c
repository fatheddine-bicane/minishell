/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 12:43:32 by fbicane           #+#    #+#             */
/*   Updated: 2025/06/11 23:28:49 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

void	is_group(t_shell *shell)
{
	pid_t	pid;
	/*t_cmd	*tmp;*/

	/*if (true == shell->is_pipe)*/
	/*	free_pipex(&shell->pipex);*/
	shell->is_group = true;
	pid = fork();
	if (0 == pid)
	{
		if (C_EXEC == shell->cmd->u_as.group.cmd->type)
		{
			shell->cmd = shell->cmd->u_as.group.cmd;
			is_command(shell, true, -1);
		}
		else if (C_REDIRECT == shell->cmd->u_as.group.cmd->type)
		{
			shell->cmd = shell->cmd->u_as.group.cmd;
			is_redirection(shell, true, -1);
			if (NULL != shell->heredocs_files)
			{
				ft_free_arr(shell->heredocs_files); // (cat <<s), cmd | (cat <<s)
				shell->heredocs_files = NULL;
			}
			// double free: (cat <<s >file) && ls | wc | cat >>file && (echo >>file) && ls
		}
		else if (C_PIPE == shell->cmd->u_as.group.cmd->type)
		{
			shell->cmd = shell->cmd->u_as.group.cmd;
			is_pipe(shell);
			if (shell->heredocs_files)
			{
				ft_printf(RED"free herdocs" RESET);
				ft_free_arr(shell->heredocs_files);
			}
		}
		else if (C_GROUP == shell->cmd->u_as.group.cmd->type)
		{
			shell->cmd = shell->cmd->u_as.group.cmd;
			is_group(shell);
		}
		else if (C_COMPOUND == shell->cmd->u_as.group.cmd->type)
		{
			shell->cmd = shell->cmd->u_as.group.cmd;
			is_compound(shell);
		}
		/*ft_putstr_fd(RED"failed to execute\n"RESET, 2);*/

		// WARNING: might leed to double free
		/*if (true == shell->is_pipe)*/
		/*{*/
		/*	free_pipex(&shell->pipex);*/
		/*}*/
		free_my_envp(&shell->my_envp);
		/*ft_free_arr(shell->heredocs_files); //????? might be invalid u freed it in is command*/
		ast_free(shell->root_to_free);
		exit(shell->exit_status);
	}
	else if (0 != pid)
	{
		wait_child(pid, shell);
		/*if (true == shell->is_pipe)*/
		/*{*/
			/*ft_putstr_fd(RED"freeing pipex struct\n"RESET, 2);*/
			/*free_my_envp(&shell->my_envp);*/

			// WARNING:
			/*ft_free_arr(shell->heredocs_files);*/
			// cat <<s | wc && (cat <<d)
			// thiscauses double free u free themmry in subshel parent and try to free it in unlink

			/*shell->heredocs_files = NULL; // Add this line to prevent double free*/
			/*free_pipex(&shell->pipex);*/
		/*}*/
	}
}
