/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 09:51:55 by piotrwojnar       #+#    #+#             */
/*   Updated: 2025/02/10 12:35:41 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	ft_error(int code)
{
	if (code == -1)
		ft_printf("Error: Wrong file format!\n");
	else if (code == -2)
		ft_printf("Error: No player start position found in the map!\n");
	else if (code == -3)
		ft_printf("Error: No player start position found in the map!\n");
	else if (code == -4)
		ft_printf("Error: Multiple player start positions found!\n");
	else if (code == -5)
		ft_printf("Error: Unknown Symbol found in the map!\n");
	else if (code == -6)
		ft_printf("Error: Empty space detected!\n");
	else if (code == -7)
		ft_printf("Error: Invalid color format! Expected R,G,B values.\n");
	else if (code == -8)
		ft_printf("Error: Duplicate color directive found.\n");
	else if (code == -9)
		ft_printf("Error: Color value out of range! Expected 0-255.\n");
	else if (code == -10)
		ft_printf("Error: Unable to open .cub file!\n");
	else if (code == -11)
		ft_printf("Error: No valid map data found in the file!\n");
	else if (code == -12)
		ft_printf("Error: Memory allocation failed while processing path!\n");
	exit(1);
}

void	ft_wall_err(const char *message, int value, const char *context)
{
	ft_printf("Error: %s %s %d!\n", message, context, value);
	exit(1);
}

void	ft_texture_err(const char *message, int index, t_resources *res,
	mlx_t *mlx)
{
	ft_printf("[ERROR] %s (Index: %d)\n", message, index);
	cleanup_textures(res, mlx);
	exit(1);
}

char	*err_path(const char *message, char *line)
{
	ft_printf("[ERROR] %s: '%s'\n", message, line);
	return (NULL);
}
