/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 10:32:27 by fbicane           #+#    #+#             */
/*   Updated: 2024/11/25 11:05:13 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../my_library.h"

int	ft_putunint(unsigned int n)
{
	if (n == 0)
	{
		ft_putchar(48);
		return (1);
	}
	if (n > 9)
		ft_putunint(n / 10);
	ft_putchar(n % 10 + 48);
	return (ft_nb_count(n));
}
