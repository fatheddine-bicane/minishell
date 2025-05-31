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

void	export_error(t_shell *shell, int error_mssg)
{
	(void)shell;
	if (1 == error_mssg)
	{
		printf("test");
	}
}
