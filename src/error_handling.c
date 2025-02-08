/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 09:51:55 by piotrwojnar       #+#    #+#             */
/*   Updated: 2025/02/08 15:37:33 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	ft_error(int code)
{
	if (code == -1)
	{
		ft_printf("Error: Wrong file format!\n");
	}
	else if (code == -2)
	{
		ft_printf("Error: No player start position found in the map!\n");
	}
	else if (code == -3)
	{
		ft_printf("Error: No player start position found in the map!\n");
	}
	else if (code == -4)
	{
		ft_printf("Error: Multiple player start positions found!\n");
	}
	else if (code == -5)
	{
		ft_printf("Error: Unknown Symbol found in the map!\n");
	}
	else if (code == -6)
	{
		ft_printf("Error: Empty space detected!\n");
	}
	exit(1);
}

void	ft_wall_err(const char *message, int value, const char *context)
{
	ft_printf("Error: %s %s %d!\n", message, context, value);
	exit(1);
}
