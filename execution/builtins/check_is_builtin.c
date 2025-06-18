/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_is_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <fbicane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:12:33 by fbicane           #+#    #+#             */
/*   Updated: 2025/05/28 14:12:47 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishel.h"

bool	ft_is_builtin(char *command)
{
	if (1 == ft_strlen(command))
		return (false);
	if (0 == ft_strncmp(command, "echo", ft_strlen(command)))
		return (true);
	else if (0 == ft_strncmp(command, "cd", ft_strlen(command)))
		return (true);
	else if (0 == ft_strncmp(command, "pwd", ft_strlen(command)))
		return (true);
	else if (0 == ft_strncmp(command, "export", ft_strlen(command)))
		return (true);
	else if (0 == ft_strncmp(command, "unset", ft_strlen(command)))
		return (true);
	else if (0 == ft_strncmp(command, "env", ft_strlen(command)))
		return (true);
	else if (0 == ft_strncmp(command, "exit", ft_strlen(command)))
		return (true);
	else
		return (false);
}
