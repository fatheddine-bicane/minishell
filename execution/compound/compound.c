/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compound.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 18:27:02 by fbicane           #+#    #+#             */
/*   Updated: 2025/06/05 19:28:53 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

void	run_compound_side(t_shell *shell)
{
	if (C_EXEC == shell->cmd->type)
	{
		is_command(shell, true, -1);
	}
	else if (C_REDIRECT == shell->cmd->type)
	{
		is_redirection(shell, true, -1);
	}
	else if (C_PIPE == shell->cmd->type)
	{
		is_pipe(shell);
	}
	else if (C_GROUP == shell->cmd->type)
	{
		is_group(shell);
	}
	else if (C_COMPOUND == shell->cmd->type)
	{
		is_compound(shell);
	}
}

void	is_compound(t_shell *shell)
{
	t_cmd	*tmp;

	tmp = shell->cmd;
	if (T_AND == shell->cmd->u_as.compound.type)
	{
		shell->cmd = tmp->u_as.compound.left;
		run_compound_side(shell);
		/*printf("coumpound condition%s\n", ft_itoa(shell->exit_status));*/
		if (0 == shell->exit_status)
		{
			shell->cmd = tmp->u_as.compound.right;
			run_compound_side(shell);
		}
	}
	else if (T_OR == shell->cmd->u_as.compound.type)
	{
		shell->cmd = tmp->u_as.compound.left;
		run_compound_side(shell);
		if (0 != shell->exit_status)
		{
			shell->cmd = tmp->u_as.compound.right;
			run_compound_side(shell);
		}
	}
}
