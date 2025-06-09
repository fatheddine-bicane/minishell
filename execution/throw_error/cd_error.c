/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 15:50:37 by fbicane           #+#    #+#             */
/*   Updated: 2025/05/31 16:34:19 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

void	cd_error(t_cd *cd, int error_mssg)
{
	if (1 == error_mssg)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		cd->shell->exit_status = 1;
		return (free(cd->home_path), free(cd->oldpwd));
	}
	else if (2 == error_mssg)
	{
		ft_putstr_fd("minishell: chdir() error\n", 2);
		cd->shell->exit_status = 1;
		return (free(cd->home_path), free(cd->oldpwd));
	}
	else if (3 == error_mssg)
	{
		perror(cd->shell->cmd->u_as.exec.argv[1]);
		cd->shell->exit_status = 1;
		return (free(cd->oldpwd), free(cd->home_path));
	}
}
