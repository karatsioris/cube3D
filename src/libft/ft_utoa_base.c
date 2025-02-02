/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 20:24:19 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/09/13 10:30:35 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_utoa_base(unsigned long value, const char *base)
{
	unsigned long	base_len;
	char			*str;
	unsigned long	temp;
	int				size;

	base_len = ft_strlen(base);
	temp = value;
	size = 0;
	if (!value)
		size = 1;
	while (temp)
	{
		temp /= base_len;
		size++;
	}
	str = (char *)malloc(1 * (size + 1));
	if (!str)
		return (NULL);
	str[size] = '\0';
	while (size > 0)
	{
		str[--size] = base[value % base_len];
		value /= base_len;
	}
	return (str);
}
