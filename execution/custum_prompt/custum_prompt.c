/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custum_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 16:28:22 by fbicane           #+#    #+#             */
/*   Updated: 2025/06/09 16:32:35 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"


char	*custum_prompt(t_shell shell)
{
	char	path[PATH_MAX];
	char	*prompt;
	char	*to_free;
	char	*exit_stat;
	int		slash_count;
	int		i;

	getcwd(path, sizeof(path));
	i = 0;
	slash_count = 3;
	while (path[i])
	{
		if (0 == slash_count)
			break ;
		if (path[i] && '/' == path[i])
			slash_count--;
		i++;
	}
	prompt = ft_strjoin(BLUE " [ ~/", path + i);
	to_free = prompt;
	prompt = ft_strjoin(prompt, "]");
	free(to_free);
	to_free = prompt;
	prompt = ft_strjoin(prompt, RESET);
	free(to_free);
	to_free = prompt;
	if (shell.exit_status == 0)
	{
		to_free = prompt;
		prompt = ft_strjoin(prompt, GREEN " [✔]>> " RESET);
		free(to_free);
	}
	else
	{
		to_free = prompt;
		prompt = ft_strjoin(prompt, RED " [");
		free(to_free);
		exit_stat = ft_itoa(shell.exit_status);
		to_free = prompt;
		prompt = ft_strjoin(prompt, exit_stat);
		free(to_free);
		free(exit_stat);
		to_free = prompt;
		prompt = ft_strjoin(prompt, "✘]>> " RESET);
		free(to_free);
	}
	return (prompt);
}

