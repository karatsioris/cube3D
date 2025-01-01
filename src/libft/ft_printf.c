/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 20:47:33 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/07/23 20:06:19 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	handle_format(char specifier, va_list ap)
{
	if (specifier == 'd' || specifier == 'i')
		return (ft_putnbr_fd(va_arg(ap, int), 1));
	else if (specifier == 'x' || specifier == 'X')
		return (print_hex(va_arg(ap, unsigned int), specifier == 'X', 1));
	else if (specifier == 'u')
		return (ft_putunsignednbr_fd(va_arg(ap, unsigned int), 1));
	else if (specifier == 's')
		return (ft_putstr_fd(va_arg(ap, char *), 1));
	else if (specifier == 'c')
		return (ft_putchar_fd((char)va_arg(ap, int), 1));
	else if (specifier == 'p')
	{
		ft_putstr_fd("0x", 1);
		return (2 + print_hex((unsigned long)va_arg(ap, void *), 0, 1));
	}
	else
		return (ft_putchar_fd(specifier, 1));
}

int	ft_printf(const char *format_str, ...)
{
	va_list	ap;
	int		printed_chars;

	printed_chars = 0;
	va_start(ap, format_str);
	while (*format_str)
	{
		if (*format_str == '%')
		{
			format_str++;
			if (*format_str)
				printed_chars += handle_format(*format_str++, ap);
		}
		else
			printed_chars += write(1, format_str++, 1);
	}
	va_end(ap);
	return (printed_chars);
}
