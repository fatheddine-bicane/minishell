/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicane <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:21:38 by fbicane           #+#    #+#             */
/*   Updated: 2024/12/13 18:56:01 by fbicane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../my_library.h"

int	ft_formatchek(va_list args, char c)
{
	int	count;

	count = 0;
	if (c == '%')
		count = ft_putchar('%');
	if (c == 'c')
		count = ft_putchar(va_arg(args, int));
	if (c == 's')
		count = ft_putstr(va_arg(args, char *));
	if (c == 'd' || c == 'i')
		count = ft_putnbr(va_arg(args, int));
	if (c == 'x')
		count = ft_puthexa(va_arg(args, unsigned int), 'x');
	if (c == 'X')
		count = ft_puthexa(va_arg(args, unsigned int), 'X');
	if (c == 'u')
		count = ft_putunint(va_arg(args, unsigned int));
	if (c == 'p')
		count = ft_putadrr(va_arg(args, void *));
	return (count);
}

int	ft_iter_str(const char *str, va_list args, int i, int count)
{
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1])
		{
			i++;
			count += ft_formatchek(args, str[i]);
			i++;
		}
		else if (str[i] == '%' && str[i + 1] == '\0')
		{
			va_end(args);
			return (-1);
		}
		else
		{
			ft_putchar(str[i++]);
			count++;
		}
	}
	va_end(args);
	return (count);
}

int	ft_printf(const char *str, ...)
{
	int		count;
	int		i;
	va_list	args;

	if (!str)
		return (-1);
	i = 0;
	count = 0;
	va_start(args, str);
	return (ft_iter_str(str, args, i, count));
}
