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
	redirect = open(file_name, O_RDONLY | O_CREAT | O_APPEND, 0664);
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
	/*int	redirect;*/

	i = 0;
	while (redirections[i])
	{
		if ('>' == redirections[i][0])
		{
			ft_redirect_output(redirections[i] + 1);
			/*redirect = open(redirections[i] + 1, O_WRONLY | O_CREAT | O_TRUNC, 0664);*/
			/*if (-1 == redirect)*/
			/*	return ;*/
			/*if (-1 == dup2(redirect, STDOUT_FILENO))*/
			/*{*/
			/*	close(redirect);*/
			/*	return; //TODO:error mssg*/
			/*}*/
		}
		else if ('<' == redirections[i][0])
		{
			ft_redirect_input(redirections[i] + 1);
			/*redirect = open(redirections[i] + 1, O_RDONLY);*/
			/*if (-1 == redirect)*/
			/*	return ;*/
			/*if (-1 == dup2(redirect, STDIN_FILENO))*/
			/*{*/
			/*	close(redirect);*/
			/*	return; //TODO:error mssg*/
			/*}*/
		}
		else if ('>' == redirections[i][0] && '>' == redirections[i][1])
		{
			ft_appent_output(redirections[i] + 2);
			/*redirect = open(redirections[i] + 2, O_RDONLY | O_CREAT | O_APPEND, 0664);*/
			/*if (-1 == redirect)*/
			/*	return ;*/
			/*if (-1 == dup2(redirect, STDOUT_FILENO))*/
			/*{*/
			/*	close(redirect);*/
			/*	return; //TODO:error mssg*/
			/*}*/
		}
		else if ('<' == redirections[i][0] && '<' == redirections[i][1])
			ft_here_doc(redirections[i] + 2);
		i++;
	}
}
