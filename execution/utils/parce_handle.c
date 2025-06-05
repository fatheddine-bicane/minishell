/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 13:43:15 by fbicane           #+#    #+#             */
/*   Updated: 2025/05/29 16:52:57 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

void is_command(t_shell *shell, bool to_fork, pid_t pid_r)
{
	if (false == shell->redirections_status)
	{
		shell->exit_status = 1;
		return;
	}
	if (ft_is_builtin(shell->cmd->u_as.exec.argv[0]))
	{
		run_bultins(shell);
	}
	else
	{
		if (to_fork)
			ft_apply_comm(shell, true, -3);
		if (!to_fork)
			ft_apply_comm(shell, false, pid_r);
	}
}

void is_redirection(t_shell *shell, bool to_fork, pid_t pid_r)
{
	t_cmd *tmp;
	t_str_builder *sb;

	/*if (to_fork)*/
	/*ft_save_std_files(true);*/

	tmp = shell->cmd;
	sb = sb_create(10);
	if (sb == NULL)
		return;
	while (tmp != NULL && tmp->type == C_REDIRECT)
	{
		sb_append_str(sb, token_type_str(tmp->u_as.redirect.type), 0);
		sb_append_str(sb, tmp->u_as.redirect.file, 0);
		tmp = tmp->u_as.redirect.next;
	}
	char **redirects = sb_build(sb);

	if (!handle_redirections(redirects, shell))
	{
		shell->redirections_status = false;
		sn_strs_free(redirects);
		if (0 == pid_r && !to_fork)
		{
			free_my_envp(&shell->my_envp);
			/*exit(shell->exit_status);*/
		}
		/*if (to_fork)*/
		std_files(RESTORE_BOTH);
		/*ft_save_std_files(false);*/
		return;
	}
	sn_strs_free(redirects);

	if (tmp)
	{
		t_cmd *tmp2 = shell->cmd;
		shell->cmd = tmp;
		is_command(shell, to_fork, pid_r);
		shell->cmd = tmp2;
	}
	if (to_fork)
		std_files(RESTORE_BOTH);
	/*ft_save_std_files(false);*/
}

/*static void	ft_wait_pids(t_list *pids, int *exit_stat)*/
/*{*/
/*	pid_t	pid;*/
/**/
/*	while (pids)*/
/*	{*/
/*		pid = ft_atoi((char *)pids->content);*/
/*waitpid(pid, NULL, 0);*/
/*		wait_child(pid, exit_stat);*/
/*		pids = pids->next;*/
/*	}*/
/*}*/

/*void	is_pipe(t_cmd *cmd, t_list **my_envp, int *exit_stat, int depth)*/
/*{*/
/*	static pid_t	pid;*/
/*	static int		prev_pipe[2]; // INFO: hold pipes fds*/
/*	static int		fd[2];*/
/*	static t_list	*pids;*/
/**/
/**/
/**/
/*	if (depth == 0)*/
/*	{*/
/*		pids = NULL;*/
/*		prev_pipe[0] = -1;*/
/*		prev_pipe[1] = -1;*/
/*	}*/
/**/
/**/
/*	if (cmd->u_as.pipe.left->type == C_PIPE)*/
/*	{*/
/*		is_pipe(cmd->u_as.pipe.left, my_envp, exit_stat, depth + 1);*/
/*	}*/
/**/
/*	if (0 != depth)*/
/*	{*/
/*		if (-1 == pipe(fd))*/
/*		{*/
/*			(*exit_stat) = -1;*/
/*			perror("pipe()");*/
/*			return;*/
/*		}*/
/*	}*/
/**/
/*	pid = fork();*/
/*	if (pid != 0)*/
/*	{*/
/*		ft_lstadd_back(&pids, ft_lstnew(ft_itoa(pid))); // INFO: save all pids*/
/*	}*/
/**/
/*	if (0 == pid)*/
/*	{*/
/*		if (-1  != prev_pipe[0])*/
/*		{*/
/*			if (-1 == dup2(prev_pipe[0], STDIN_FILENO))*/
/*				return; // TODO: error mssg*/
/*		}*/
/*		if (0 != depth)*/
/*		{*/
/*			if (-1 == dup2(fd[1], STDOUT_FILENO))*/
/*				return; // TODO: error mssg*/
/*		}*/
/**/
/*		if (-1 != prev_pipe[0])*/
/*			close(prev_pipe[0]);*/
/*		if (-1 != prev_pipe[1])*/
/*			close(prev_pipe[1]);*/
/**/
/*		if (0 != depth)*/
/*		{*/
/*			close(fd[0]);*/
/*			close(fd[1]);*/
/*		}*/
/**/
/**/
/**/
/**/
/*		//INFO: execution*/
/*		if (cmd->u_as.pipe.left->type == C_REDIRECT)*/
/*		{*/
/*			// call redirect*/
/*			is_redirection(shell);*/
/*		}*/
/*if (cmd->u_as.pipe.left->type == C_GROUP)*/
/*{*/
/*	// call subshell*/
/*}*/
/*		if (cmd->u_as.pipe.left->type == C_EXEC)*/
/*		{*/
/*			// call exec*/
/*			is_command(cmd->u_as.pipe.left, my_envp, exit_stat);*/
/*		}*/
/**/
/**/
/*		if (cmd->u_as.pipe.right->type == C_EXEC)*/
/*			is_command(cmd->u_as.pipe.right, my_envp, exit_stat);*/
/*		if (cmd->u_as.pipe.right->type == C_REDIRECT)*/
/*			is_redirection(cmd->u_as.pipe.right, my_envp, exit_stat);*/
/*	}*/
/**/
/**/
/*	else*/
/*	{*/
/*		if (-1 != prev_pipe[0])*/
/*			close(prev_pipe[0]);*/
/*		if (-1 != prev_pipe[1])*/
/*			close(prev_pipe[1]);*/
/**/
/*		if (0 != depth)*/
/*		{*/
/*			prev_pipe[0] = fd[0];*/
/*			prev_pipe[1] = fd[1];*/
/*		}*/
/*	}*/
/*	ft_wait_pids(pids, exit_stat); // TODO: check if it waits for pids*/
/*}*/
/*{*/
/*	t_cmd *tmp;*/
/**/
/*	is_redirect(cmd);*/
/*	tmp = cmd->u_as.redirect.next;*/
/*	if (tmp == NULL)*/
/*		return;*/
/*	while (tmp != NULL)*/
/*	{*/
/*		if (tmp->type == C_REDIRECT) {*/
/**/
/*		}*/
/*		tmp = cmd->u_as.redirect.next;*/
/*	}*/
/**/
/*	ft_pipex(cmd->u_as.redirect.type == T_HEREDOC)*/
/*		cmd->u_as.redirect.next->type*/
/*}*/
