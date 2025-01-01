/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:38:13 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/09/13 10:15:49 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t n, size_t size)
{
	size_t	i;
	size_t	nb;
	char	*p;

	i = 0;
	nb = n * size;
	p = malloc(nb);
	if (p != NULL)
	{
		while (i < nb)
		{
			p[i] = 0;
			i++;
		}
	}
	return (p);
}
