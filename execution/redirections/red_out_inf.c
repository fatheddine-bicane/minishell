/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_out_inf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 11:16:19 by fbicane           #+#    #+#             */
/*   Updated: 2025/04/23 18:14:01 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

void	ft_save_std_files(bool save)
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
	// TODO: close used files
}

static void	ft_redirect_output(char *file_name)
{
	int	redirect;

	redirect = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (-1 == redirect)
		return ; // TODO: error mssg
	if (-1 == dup2(redirect, STDOUT_FILENO))
	{
		close(redirect);
		return; // TODO: error mssg
	}
	close(redirect);
}

static void	ft_appent_output(char *file_name)
{
	int	redirect;
	redirect = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (-1 == redirect)
		return ;
	if (-1 == dup2(redirect, STDOUT_FILENO))
	{
		close(redirect);
		return; //TODO:error mssg
	}
	close(redirect);
}

static void	ft_redirect_input(char *file_name)
{
	int	redirect;
	redirect = open(file_name, O_RDONLY);
	if (-1 == redirect)
		return ;
	if (-1 == dup2(redirect, STDIN_FILENO))
	{
		close(redirect);
		return; //TODO:error mssg
	}
	close(redirect);
}

void	ft_handle_redirections(char **redirections)
{
	int	i;

	i = 0;
	while (redirections[i])
	{
		if (!ft_strncmp(">>", redirections[i], 2))
		{
			i++;
			ft_appent_output(redirections[i]);
		}
		else if (!ft_strncmp("<<", redirections[i], 2))
		{
			i++;
			ft_here_doc(redirections[i]);
		}
		else if (!ft_strncmp(">", redirections[i], 1))
		{
			i++;
			ft_redirect_output(redirections[i]);
		}
		else if (!ft_strncmp("<", redirections[i], 1))
		{
			i++;
			ft_redirect_input(redirections[i]);
		}
		i++;
	}
}
