/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 22:52:58 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/09/13 10:22:18 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr_fd(const char *s, int fd)
{
	int	count;

	count = 0;
	if (!s)
	{
		s = "(null)";
	}
	while (*s)
	{
		ft_putchar_fd(*s++, fd);
		count++;
	}
	return (count);
}
