/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putadrr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 11:08:15 by fbicane           #+#    #+#             */
/*   Updated: 2024/11/26 15:28:13 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../my_library.h"

int	ft_puthexa_adrr(unsigned long n)
{
	char	*base_x;
	int		count;

	count = 0;
	base_x = "0123456789abcdef";
	if (n == 0)
	{
		count += ft_putchar('0');
		return (count);
	}
	if (n >= 16)
		count += ft_puthexa_adrr(n / 16);
	count += ft_putchar(base_x[n % 16]);
	return (count);
}

int	ft_putadrr(void *ptr)
{
	unsigned long	ptr_adrr;
	int				count;

	if (!ptr)
		return (ft_putstr("(nil)"));
	ptr_adrr = (unsigned long)ptr;
	count = 0;
	count += ft_putstr("0x");
	count += ft_puthexa_adrr(ptr_adrr);
	return (count);
}
