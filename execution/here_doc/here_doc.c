/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 17:22:24 by fbicane           #+#    #+#             */
/*   Updated: 2025/06/11 14:21:02 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

static char	*ft_apend_new_line(char *str)
{
	int		i;
	char	*str2;

	i = 0;
	str2 = malloc(sizeof(char) * (ft_strlen(str) + 2));
	while (str[i])
	{
		str2[i] = str[i];
		i++;
	}
	str2[i] = '\n';
	i++;
	str2[i] = '\0';
	return (str2);
}

static char	*ft_creat_input(char *limiter)
{
	char	*str;
	char	*join;
	char	*join_m;
	char	*limiter_n;

	join = ft_strdup("");
	limiter_n = ft_apend_new_line(limiter);
	str = readline(YELLOW "[heredoc]>> " RESET);
	join_m = str;
	str = ft_strjoin(str, "\n");
	while (str && ft_strncmp(str, limiter_n, ft_strlen(limiter_n)))
	{
		join_m = join;
		join = ft_strjoin(join, str);
		free(join_m);
		free(str);
		str = readline(YELLOW "[heredoc]>> " RESET);
		join_m = str;
		str = ft_strjoin(str, "\n");
		if (NULL == str)
		{
			ft_putstr_fd("warning: heredoc delimited by end-of-file", 2);
			free(limiter_n);
			return (join);
		}
	}
	free(str);
	free(limiter_n);
	return (join);
}

char	*random_name(void)
{
	char	*file_name;
	char	*file_name_m;
	char	*tmp_path;
	int		random_file;
	char	path[PATH_MAX];
	ssize_t	b_read;
	int		i;

	file_name = malloc(sizeof(char) * 10);
	if (!file_name)
		return (NULL);
	random_file = open("/dev/urandom", O_RDONLY);
	if (-1 == random_file)
		return (perror("read()"), free(file_name), NULL);
	b_read = read(random_file, file_name, 9);
	if (-1 == b_read)
		return (perror("read()"), free(file_name), NULL);
	file_name[b_read] = '\0';
	i = -1;
	while (file_name[++i])
		file_name[i] = file_name[i] % 26 + 'a';
	close(random_file);
	getcwd(path, sizeof(path));
	tmp_path = ft_strjoin(path, "/execution/tmp/");
	file_name_m = file_name;
	file_name = ft_strjoin(tmp_path, file_name);
	return (free(tmp_path), free(file_name_m), file_name);
}




char	*creat_here_doc(char *delimiter, t_shell *shell)
{
	char	*input;
	char	*file_name;
	int		inf;
	pid_t	pid;

	ignore_signals_parrent();
	file_name = random_name();
	pid = fork();
	if (-1 == pid)
	{
		perror("fork()");
		setup_signals();
		return (NULL);
	}
	if (0 == pid)
	{
		setup_signals_heredoc();
		input = ft_creat_input(delimiter);
		// printf("file name: %s\n", file_name);
		inf = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (-1 == inf)
			return(perror("open()"), NULL);
		ft_putstr_fd(input, inf);
		free(input);
		close(inf);
		sb_free(shell->sb_to_free);
		ft_free_arr(shell->heredocs_files);
		ft_free_arr(shell->heredocs_delemiters);
		free_my_envp(&shell->my_envp);
		ast_free(shell->root_to_free);
		free(file_name);
		exit(0);
	}
	else if (0 != pid)
	{
		wait_child(pid, shell);
		if (130 == shell->exit_status)
			return (NULL);
		setup_signals();
	}
	return (file_name);
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
