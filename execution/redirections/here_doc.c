/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 17:22:24 by fbicane           #+#    #+#             */
/*   Updated: 2025/06/03 14:30:27 by fbicane          ###   ########.fr       */
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
	str = get_next_line(0);
	while (str && ft_strncmp(str, limiter_n, ft_strlen(limiter_n)))
	{
		join_m = join;
		join = ft_strjoin(join, str);
		free(join_m);
		free(str);
		str = get_next_line(0);
	}
	free(str);
	get_next_line(-1);
	free(limiter_n);
	return (join);
}

char	*random_name(void)
{
	char	*file_name;
	int		random_file;
	int		i;

	file_name = malloc(sizeof(char) * 10);
	if (!file_name)
		return (NULL);
	random_file = open("/dev/urandom", O_RDONLY);
	if (-1 == random_file)
		return (perror("read()"), NULL);
	ssize_t b_read = read(random_file, file_name, 9);
	if (-1 == b_read)
		return (perror("read()"), NULL);
	file_name[b_read] = '\0';
	i = -1;
	while (file_name[++i])
		file_name[i] = file_name[i] % 26 + 'a';
	close(random_file);
	return (file_name);
}

bool	here_doc(char *delimiter, t_shell *shell)
{
	char	*input;
	char	*file_name;
	int		inf;
	pid_t	pid;

	/*std_files(RESTORE);*/
	std_files(RESTORE_STDIN);
	ignore_signals_parrent();
	file_name = random_name();
	pid = fork();
	if (-1 == pid)
	{
		perror("fork()");
		setup_signals();
		return (false);
		// WARNING: not restoring the the signals for parent
	}
	if (0 == pid)
	{
		setup_signals_child();
		input = ft_creat_input(delimiter);
		printf("file name: %s\n", file_name);
		inf = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (-1 == inf)
			return(perror("open()"), false);
		ft_putstr_fd(input, inf);
		free(input);
		close(inf);
		/*inf = open(file_name, O_RDONLY);*/
		/*if (-1 == inf)*/
		/*	return (false); // TODO: error mssg*/
		/*if (-1 == dup2(inf, STDIN_FILENO))*/
		/*	return(perror("dup2()"), false);*/
		/*close(inf);*/
		/*unlink(file_name);*/
		/*free(file_name);*/
		exit(0);
	}
	else if (0 != pid)
	{
		wait_child(pid, shell);
		if (!access(file_name, F_OK))
		{
			inf = open(file_name, O_RDONLY);
			if (-1 == inf)
			{
				unlink(file_name);
				perror("open()");
				return (false);
			}
			if (-1 == dup2(inf, STDIN_FILENO))
			{
				unlink(file_name);
				perror("dup2()");
				return (false);
			}
			close(inf);
			unlink(file_name);
			setup_signals();
			return (true);
		}
	}
	setup_signals();
	return (false);
}






















// TODO: maybe fock to fix signals
void	ft_here_doc(char *delimiter)
{
	char	*input;
	char	*file_name;
	int		inf;

	std_files(RESTORE_STDIN);
	setup_signals_heredoc(); // WARNING: it sends the sogint to main process
	input = ft_creat_input(delimiter);
	file_name = random_name();
	printf("file name: %s\n", file_name);
	inf = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (-1 == inf)
		return(perror("open()"));
	ft_putstr_fd(input, inf);
	free(input);
	close(inf);
	inf = open(file_name, O_RDONLY);
	if (-1 == inf)
		return; // TODO: error mssg
	if (-1 == dup2(inf, STDIN_FILENO))
		return(perror("dup2()"));
	close(inf);
	unlink(file_name);
	free(file_name);
}
