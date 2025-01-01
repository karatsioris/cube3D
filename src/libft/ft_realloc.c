/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 22:44:24 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/07/18 22:48:55 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *pointr, size_t original_size, size_t new_size)
{
	void	*new_pointr;

	if (new_size == 0)
	{
		free(pointr);
		return (NULL);
	}
	new_pointr = malloc(new_size);
	if (!new_pointr)
		return (NULL);
	if (pointr)
	{
		if (original_size < new_size)
			ft_memcpy(new_pointr, pointr, original_size);
		else
			ft_memcpy(new_pointr, pointr, new_size);
		free(pointr);
	}
	return (new_pointr);
}
