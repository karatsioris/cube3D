/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaratsi <kkaratsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 08:18:33 by kkaratsi          #+#    #+#             */
/*   Updated: 2025/02/07 05:37:31 by kkaratsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

uint32_t get_texture_pixel(mlx_image_t *texture, int x, int y);



void	draw_square(mlx_image_t *img, float x, float y, float size, uint32_t color)
{
	int i;
	int j;
	
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			mlx_put_pixel(img, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void draw_minimap(mlx_t *mlx, t_config *config, int pos_x, int pos_y)
{
	int x;
	int y;
	float player_x;
	float player_y;
	int MINIMAP_WIDTH = config->map.width * 20;
	int MINIMAP_HEIGHT = config->map.height * 20;

	mlx_image_t *minimap_img = mlx_new_image(mlx, MINIMAP_WIDTH, MINIMAP_HEIGHT);
	if (!minimap_img)
	{
		ft_printf("[ERROR] Failed to create minimap image\n");
		return ;
	}
	clear_image(minimap_img, 0x00000000);
	y = 0;
	while (y < config->map.height)
	{
		x = 0;
		while (x < config->map.width)
		{
			if (config->map.grid[y][x] == '1')
				draw_square(minimap_img, x * 20, y * 20, 20, 0xFA3A3A88);
			else if (config->map.grid[y][x] == '0')
				draw_square(minimap_img, x * 20, y * 20, 20, 0xFFFFFF88);
			else if (config->map.grid[y][x] == 'N' || config->map.grid[y][x] == 'S'
				|| config->map.grid[y][x] == 'E' || config->map.grid[y][x] == 'W')
				draw_square(minimap_img, x * 20, y * 20, 20, 0xFFFFFFFF);
			x++;
		}
		y++;
	}
	// Draw the player on the minimap
    player_x = config->player.x * 20;
    player_y = config->player.y * 20;

	//  // Optionally, draw the player's direction
    int size = 15;
	int i = 0;
    while (i < size)
    {
		int x = player_x + i * cosf(config->player.angle);
        int y = player_y + i * sinf(config->player.angle);
		draw_square(minimap_img, x, y, 2, 0x1B10B2FF); // Blue color for direction
        // mlx_put_pixel(minimap_img, x, y, 0x1056B200); // Black color for direction
		i++;
    }
	draw_square(minimap_img, player_x - 4, player_y - 4, 10, 0x6EFA3AFF); // Green color for player



 	// Draw the raycasting lines on the minimap
    // for (int i = 0; i < config->num_rays; i++)
    // {
    //     int ray_end_x = config->rays[i].end_x * 10;
    //     int ray_end_y = config->rays[i].end_y * 10;
    //     draw_line(minimap_img, player_x, player_y, ray_end_x, ray_end_y, 0x0000FFFF); // blue color for rays
    // }


	// Draw the minimap onto the main image at the specified position
	draw_minimap_in_main_image(config->img, minimap_img, pos_x, pos_y);

	// Clean up the minimap image
    mlx_delete_image(mlx, minimap_img);
	  // Ensure the main image is updated
    mlx_image_to_window(mlx, config->img, 0, 0);
}

void draw_minimap_in_main_image(mlx_image_t *main_img, mlx_image_t *minimap_img, int pos_x, int pos_y)
{
	int x;
	int y;
	int MINIMAP_WIDTH = minimap_img->width;
	int MINIMAP_HEIGHT = minimap_img->height;

	  // Ensure the minimap fits within the main image
    if ((uint32_t)(pos_x + MINIMAP_WIDTH) > main_img->width || (uint32_t)(pos_y + MINIMAP_HEIGHT) > main_img->height)
    {
        ft_printf("[ERROR] Minimap position out of bounds\n");
        return;
    }
	y = 0;
	while (y < MINIMAP_HEIGHT)
	{
		x = 0;
		while (x < MINIMAP_WIDTH)
		{
			uint32_t color = get_texture_pixel(minimap_img, x, y);
			mlx_put_pixel(main_img, pos_x + x, pos_y + y, color);
			x++;
		}
		y++;
	}
}


// void draw_line(mlx_image_t *img, int x0, int y0, int x1, int y1, uint32_t color)
// {
//     int dx = abs(x1 - x0);
//     int dy = abs(y1 - y0);
//     int sx = (x0 < x1) ? 1 : -1;
//     int sy = (y0 < y1) ? 1 : -1;
//     int err = dx - dy;

//     while (1)
//     {
//         mlx_put_pixel(img, x0, y0, color);

//         if (x0 == x1 && y0 == y1)
//             break;

//         int e2 = 2 * err;
//         if (e2 > -dy)
//         {
//             err -= dy;
//             x0 += sx;
//         }
//         if (e2 < dx)
//         {
//             err += dx;
//             y0 += sy;
//         }
//     }
// }


