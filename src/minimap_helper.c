/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 18:28:15 by pwojnaro          #+#    #+#             */
/*   Updated: 2025/02/07 18:53:13 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

mlx_image_t	*create_minimap_image(mlx_t *mlx, int width, int height)
{
	mlx_image_t	*minimap_img;

	minimap_img = mlx_new_image(mlx, width, height);
	if (!minimap_img)
	{
		ft_printf("[ERROR] Failed to create minimap image\n");
		return (NULL);
	}
	clear_image(minimap_img, 0x00000000);
	return (minimap_img);
}

uint32_t	get_tile_color(char tile)
{
	if (tile == '1')
		return (0xFA3A3A88);
	else if (tile == '0')
		return (0xFFFFFF88);
	else if (tile == 'N' || tile == 'S' || tile == 'E' || tile == 'W')
		return (0xFFFFFFFF);
	return (0x00000000);
}

void	draw_tile(mlx_image_t *minimap_img, int x, int y, uint32_t color)
{
	t_square	square;

	square.x = x * 20;
	square.y = y * 20;
	square.size = 20;
	square.color = color;
	draw_square(minimap_img, square);
}

void	draw_map_grid(mlx_image_t *minimap_img, t_config *config)
{
	int	x;
	int	y;

	y = 0;
	while (y < config->map.height)
	{
		x = 0;
		while (x < config->map.width)
		{
			draw_tile(minimap_img, x, y,
				get_tile_color(config->map.grid[y][x]));
			x++;
		}
		y++;
	}
}
