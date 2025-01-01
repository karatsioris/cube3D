/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 23:39:34 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/03/21 21:58:49 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_fd(int n, int fd)
{
	int		i;
	int		written;

	if (n == -2147483648)
		return (ft_putstr_fd("-2147483648", fd));
	if (n < 0)
	{
		written = ft_putchar_fd('-', fd);
		if (written == -1)
			return (-1);
		i = ft_putnbr_fd(-n, fd);
		return (i + 1);
	}
	if (n > 9)
	{
		i = ft_putnbr_fd(n / 10, fd);
		if (i == -1)
			return (-1);
		written = ft_putchar_fd(n % 10 + '0', fd);
		if (written == -1)
			return (-1);
		return (i + written);
	}
	return (ft_putchar_fd('0' + n, fd));
}
