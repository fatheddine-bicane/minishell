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

void	ft_redirect_out(char *ouf_name)
{
	int	ouf;

	ouf = open(ouf_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (-1 == ouf)
		return ;
	if (-1 == dup2(ouf, STDOUT_FILENO))
		return ;
	// TODO: close ouf
}

void	ft_redirect_inf(char *inf_file)
{
	int	inf;

	inf = open(inf_file, O_RDONLY);
	if (-1 == inf)
		return ;
	if (-1 == dup2(inf, STDIN_FILENO))
		return ;
	// TODO: close inf
}
