/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 22:37:22 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/03/13 22:37:41 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*destination;
	const unsigned char	*source;

	if (!dst && !src)
		return (0);
	destination = (unsigned char *)dst;
	source = (const unsigned char *)src;
	if (destination > source)
	{
		while (len--)
			destination[len] = source[len];
	}
	else
	{
		while (len--)
		{
			*destination = *source;
			destination++;
			source++;
		}
	}
	return (dst);
}
