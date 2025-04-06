/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 17:51:12 by fbicane           #+#    #+#             */
/*   Updated: 2024/11/25 11:18:24 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../my_library.h"

int	ft_putnbr(int n)
{
	long	n_long;

	n_long = n;
	if (n_long < 0)
	{
		ft_putchar('-');
		n_long *= -1;
	}
	if (n_long > 9)
	{
		ft_putnbr(n_long / 10);
	}
	ft_putchar(n_long % 10 + 48);
	return (ft_nb_count(n));
}
