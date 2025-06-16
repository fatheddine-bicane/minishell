/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 14:54:02 by fbicane           #+#    #+#             */
/*   Updated: 2025/06/16 15:26:58 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

static bool	append_utils(char **red, int *i, t_shell *shell)
{
	(*i)++;
	red[(*i)] = expand_single_param(red[(*i)], shell);
	if (!red[(*i)] || !red[(*i)][0])
	{
		ft_printf(RED "ambiguous redirect\n" RESET);
		shell->exit_status = 1;
		return (false);
	}
	if (!appent_output(red[(*i)]))
		return (false);
	return (true);
}

static bool	output_utils(char **red, int *i, t_shell *shell)
{
	(*i)++;
	red[(*i)] = expand_single_param(red[(*i)], shell);
	if (!red[(*i)] || !red[(*i)][0])
	{
		ft_printf(RED "ambiguous redirect\n" RESET);
		shell->exit_status = 1;
		return (false);
	}
	if (!redirect_output(red[(*i)]))
		return (false);
	return (true);
}

static bool	input_utils(char **red, int *i, t_shell *shell)
{
	(*i)++;
	red[(*i)] = expand_single_param(red[(*i)], shell);
	if (!red[(*i)] || !red[(*i)][0])
	{
		ft_printf(RED "ambiguous redirect\n" RESET);
		shell->exit_status = 1;
		return (false);
	}
	if (!redirect_input(red[(*i)]))
	{
		shell->exit_status = 1;
		return (false);
	}
	return (true);
}

static bool	handle_red_utils(char **red, int *i, t_shell *shell)
{
	if (!ft_strncmp(">", red[(*i)], 1))
	{
		if (false == output_utils(red, i, shell))
			return (false);
	}
	else if (!ft_strncmp("<", red[(*i)], 1))
	{
		if (false == input_utils(red, i, shell))
			return (false);
	}
	return (true);
}

bool	handle_redirections(char **redirections, t_shell *shell)
{
	int	i;

	i = 0;
	while (redirections[i])
	{
		if (!ft_strncmp(">>", redirections[i], 2))
		{
			if (false == append_utils(redirections, &i, shell))
				return (false);
		}
		else if (!ft_strncmp("<<", redirections[i], 2))
		{
			i++;
			if (!here_doc(shell))
				return (false);
		}
		else
		{
			if (false == handle_red_utils(redirections, &i, shell))
				return (false);
		}
		i++;
	}
	return (true);
}
