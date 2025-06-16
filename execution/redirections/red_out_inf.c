/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_out_inf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 11:16:19 by fbicane           #+#    #+#             */
/*   Updated: 2025/06/16 15:27:22 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

void	std_files(int what_to_do)
{
	static int	std_in_save;
	static int	std_out_save;

	if (SAVE == what_to_do)
	{
		std_in_save = dup(STDIN_FILENO);
		if (-1 == std_in_save)
			return (perror("dup()"));
		std_out_save = dup(STDOUT_FILENO);
		if (-1 == std_out_save)
			return (perror("dup()"));
	}
	else if (RESTORE_BOTH == what_to_do)
	{
		dup2(std_in_save, STDIN_FILENO);
		dup2(std_out_save, STDOUT_FILENO);
	}
	else if (RESTORE_STDIN == what_to_do)
	{
		dup2(std_in_save, STDIN_FILENO);
	}
	else if (RESTORE_STDOUT == what_to_do)
	{
		dup2(std_out_save, STDOUT_FILENO);
	}
}

bool	redirect_output(char *file_name)
{
	int	redirect;

	redirect = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (-1 == redirect)
	{
		perror(file_name);
		return (false);
	}
	if (-1 == dup2(redirect, STDOUT_FILENO))
	{
		perror("dup2()");
		return (false);
	}
	close(redirect);
	return (true);
}

bool	appent_output(char *file_name)
{
	int	redirect;

	redirect = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (-1 == redirect)
	{
		perror(file_name);
		return (false);
	}
	if (-1 == dup2(redirect, STDOUT_FILENO))
	{
		perror("dup2()");
		return (false);
	}
	close(redirect);
	return (true);
}

bool	redirect_input(char *file_name)
{
	int	redirect;

	redirect = open(file_name, O_RDONLY);
	if (-1 == redirect)
	{
		ft_printf(RED);
		perror(file_name);
		ft_printf(RESET);
		return (false);
	}
	if (-1 == dup2(redirect, STDIN_FILENO))
	{
		perror("dup2()");
		return (false);
	}
	close(redirect);
	return (true);
}
