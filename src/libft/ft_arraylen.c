/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arraylen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piotrwojnarowski <piotrwojnarowski@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 14:55:31 by piotrwojnar       #+#    #+#             */
/*   Updated: 2025/01/01 14:56:46 by piotrwojnar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_arraylen(char **array)
{
	size_t	i;

	i = 0;
	if (!array)
		return (0);
	while (array[i])
		i++;
	return (i);
}
