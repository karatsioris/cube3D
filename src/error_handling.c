/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piotrwojnarowski <piotrwojnarowski@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 09:51:55 by piotrwojnar       #+#    #+#             */
/*   Updated: 2025/01/01 09:54:37 by piotrwojnar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

void	ft_error(int code)
{
	if (code == -1)
	{
		ft_printf("Error: The map is not rectangular!\n");
	}
	else if (code == -2)
	{
		ft_printf("Error: Memory allocation failed!\n");
	}
	else if (code == -3)
	{
		ft_printf("Error: More than one player 'P' found in the map!\n");
	}
	else if (code == -4)
	{
		ft_printf("Error: More than one exit 'E' found in the map!\n");
	}
	else if (code == -5)
	{
		ft_printf(" Unknown Symbol found in the map!\n");
	}
	else if (code == -6)
	{
		ft_printf("Error: Initialization failed!\n");
	}
	exit(1);
}