/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 21:55:46 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/03/14 21:14:40 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*pnt1 = s1;
	const unsigned char	*pnt2 = s2;
	size_t				i;

	i = 0;
	while (n > 0)
	{
		if (pnt1[i] != pnt2[i])
		{
			return (pnt1[i] - pnt2[i]);
		}
		i++;
		n--;
	}
	return (0);
}
