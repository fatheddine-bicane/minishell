/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 17:22:24 by fbicane           #+#    #+#             */
/*   Updated: 2025/06/16 13:00:52 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

bool	is_heredoc_delimiter(char *limiter, char *src)
{
	if (limiter[0] == '\0')
		return (src[0] == '\0');
	return (ft_strncmp(src, limiter, ft_strlen(src)) == 0);
}

static bool	break_of_loop(char *limiter, char **str)
{
	if (str == NULL)
	{
		ft_printf(YELLOW"warning: heredoc delimited by end-of-file\n"RESET);
		return (true);
	}
	if (is_heredoc_delimiter(limiter, (*str)))
	{
		free((*str));
		return (true);
	}
	return (false);
}

char	*ft_creat_input(char *limiter, t_shell *shell)
{
	t_str_builder	*sb;
	char			*str;
	bool			is_quoted;

	sb = sb_create(10);
	if (sb == NULL)
		return (NULL);
	is_quoted = has_quote(limiter);
	limiter = expand_heredoc_delimiter(limiter, shell);
	while (1)
	{
		str = readline(YELLOW "[heredoc]>> " RESET);
		if (break_of_loop(limiter, &str))
			break ;
		str = expand_heredoc_body(str, shell, is_quoted);
		sb_append_str(sb, str, 0);
		sb_append_char(sb, '\n');
		free(str);
	}
	return (free(limiter), sb_build_str(sb));
}

static void	compress_file_name(char **file_name)
{
	int	i;

	i = -1;
	while ((*file_name)[++i])
		(*file_name)[i] = (*file_name)[i] % 26 + 'a';
}

char	*random_name(void)
{
	t_randome_name	r_name;
	ssize_t			b_read;

	r_name.file_name = malloc(sizeof(char) * 10);
	if (!r_name.file_name)
		return (NULL);
	r_name.random_file = open("/dev/urandom", O_RDONLY);
	if (-1 == r_name.random_file)
		return (perror("read()"), free(r_name.file_name), NULL);
	b_read = read(r_name.random_file, r_name.file_name, 9);
	if (-1 == b_read)
		return (perror("read()"), free(r_name.file_name), NULL);
	r_name.file_name[b_read] = '\0';
	compress_file_name(&r_name.file_name);
	close(r_name.random_file);
	getcwd(r_name.path, sizeof(r_name.path));
	r_name.tmp_path = ft_strjoin(r_name.path, "/execution/here_doc/");
	r_name.file_name_m = r_name.file_name;
	r_name.file_name = ft_strjoin(r_name.tmp_path, r_name.file_name);
	return (free(r_name.tmp_path), free(r_name.file_name_m), r_name.file_name);
}
