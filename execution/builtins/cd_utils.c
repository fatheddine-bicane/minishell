/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 10:36:49 by fbicane           #+#    #+#             */
/*   Updated: 2025/06/18 10:37:01 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

bool	protect_cwd_cd(t_shell *shell)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd && errno == ENOENT)
	{
		chdir("/");
		change_pwd_protections(shell);
		ft_printf(RED"getcwd: cannot access parent directories: ");
		ft_printf("No such file or directory\n"RESET);
		free(cwd);
		return (false);
	}
	free(cwd);
	return (true);
}
