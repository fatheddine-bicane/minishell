/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 12:09:04 by fbicane           #+#    #+#             */
/*   Updated: 2025/06/16 12:55:11 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

char	*creat_here_doc_child(t_shell *shell,
	t_create_heredoc *heredoc, char *delimiter)
{
	setup_signals_heredoc();
	heredoc->input = ft_creat_input(delimiter, shell);
	heredoc->inf = open(heredoc->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (-1 == heredoc->inf)
		return (perror("open()"), NULL);
	ft_putstr_fd(heredoc->input, heredoc->inf);
	free(heredoc->input);
	close(heredoc->inf);
	sb_free(shell->sb_to_free);
	ft_free_arr(shell->heredocs_files);
	ft_free_arr(shell->heredocs_delemiters);
	free_my_envp(&shell->my_envp);
	ast_free(shell->root_to_free);
	free(heredoc->file_name);
	exit(0);
}

char	*creat_here_doc(char *delimiter, t_shell *shell)
{
	t_create_heredoc	heredoc;
	pid_t				pid;

	ignore_signals_parrent();
	heredoc.file_name = random_name();
	pid = fork();
	if (-1 == pid)
		return (setup_signals(), perror("fork()"), NULL);
	if (0 == pid)
	{
		if (NULL == creat_here_doc_child(shell, &heredoc,
				delimiter))
			return (NULL);
	}
	else if (0 != pid)
	{
		wait_child(pid, shell);
		if (130 == shell->exit_status)
			return (setup_signals(), free(heredoc.file_name), NULL);
		setup_signals();
	}
	return (heredoc.file_name);
}

// INFO: used in red_out_inf.c
bool	here_doc(t_shell *shell)
{
	int	inf;

	if (!shell->heredocs_files || !shell->heredocs_files[shell->herdocs_index])
		return (false);
	inf = open(shell->heredocs_files[shell->herdocs_index], O_RDONLY);
	if (-1 == inf)
		perror("open()");
	dup2(inf, STDIN_FILENO);
	close(inf);
	shell->herdocs_index++;
	return (true);
}
