/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:36:30 by fbicane           #+#    #+#             */
/*   Updated: 2025/04/30 12:32:38 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

bool	ft_is_builtin(char *command)
{
	if (0 == ft_strncmp(command, "echo", 4))
		return (true);
	else if (0 == ft_strncmp(command, "cd", 2))
		return (true);
	else if (0 == ft_strncmp(command, "pwd", 3))
		return (true);
	else if (0 == ft_strncmp(command, "export", 6))
		return (true);
	else if (0 == ft_strncmp(command, "unset", 5))
		return (true);
	else if (0 == ft_strncmp(command, "env", 3))
		return (true);
	else if (0 == ft_strncmp(command, "exit", 4))
		return (true);
	else
		return (false);
}
