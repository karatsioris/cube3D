/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 19:13:36 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/07/18 22:02:00 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_hex(unsigned long number, int upper, int fd)
{
	char	*hexstr;
	char	*base_lower;
	char	*base_upper;
	char	*base;
	int		printed;

	base_lower = "0123456789abcdef";
	base_upper = "0123456789ABCDEF";
	printed = 0;
	if (upper)
	{
		base = base_upper;
	}
	else
	{
		base = base_lower;
	}
	hexstr = ft_utoa_base(number, base);
	if (hexstr != NULL)
	{
		printed = ft_putstr_fd(hexstr, fd);
		free(hexstr);
	}
	return (printed);
}
