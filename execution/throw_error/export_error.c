/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 18:43:12 by fbicane           #+#    #+#             */
/*   Updated: 2025/05/31 18:49:33 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

void	export_error(t_shell *shell, int *vars_i)
{
		ft_putstr_fd(shell->cmd->u_as.exec.argv[*vars_i], 2);
		ft_putstr_fd(": not a valid identifier\n", 2);
		(*vars_i)++;
}
