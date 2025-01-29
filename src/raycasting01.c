/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting01.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaratsi <kkaratsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:33:24 by kkaratsi          #+#    #+#             */
/*   Updated: 2025/01/29 14:43:32 by kkaratsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	draw_vertical_line(mlx_image_t *img, int x, int drawStart, int drawEnd, uint32_t color)
{
	int y;
	y = drawStart;
	while (y < drawEnd)
	{
		mlx_put_pixel(img, x, y, color);
		y++;
	}
}

void	calculate_draw_parameters(int window_height, float perpWallDist, int *lineHeight, int *drawStart, int *drawEnd)
{
	*lineHeight = (int)(window_height / perpWallDist);
	*drawStart = -(*lineHeight) / 2 + window_height / 2;
	if (*drawStart < 0)
		*drawStart = 0;
	*drawEnd = (*lineHeight) / 2 + window_height / 2;
	if (*drawEnd >= window_height)
		*drawEnd = window_height - 1;
}

bool cast_ray(float start_x, float start_y, float angle, int window_height, int *lineHeight, int *drawStart, int *drawEnd, t_map *map, t_config *config)
{
	t_ray	ray;

	ray.map_x = (int)start_x;
	ray.map_y = (int)start_y;
	ray.delta_dist_x = fabs(1 / tan(angle));
	ray.delta_dist_y = fabs(1 / tan(angle));
	if (angle > 3.14159)
	{
		ray.step_x = -1;
		ray.side_dist_x = (start_x - ray.map_x) * ray.delta_dist_x;
	}
	else
	{
		ray.step_x = 1;
		ray.side_dist_x = (ray.map_x + 1.0 - start_x) * ray.delta_dist_x;
	}
	if (angle > 1.5708 && angle < 4.71239)
	{
		ray.step_y = -1;
		ray.side_dist_y = (start_y - ray.map_y) * ray.delta_dist_y;
	}
	else
	{
		ray.step_y = 1;
		ray.side_dist_y = (ray.map_y + 1.0 - start_y) * ray.delta_dist_y;
	}
	while (ray.map_y >= 0 && ray.map_y < window_height && ray.map_x >= 0 && ray.map_x < WINDOW_WIDTH)
	{
		if (ray.side_dist_x < ray.side_dist_y)
		{
			ray.side_dist_x += ray.delta_dist_x;
			ray.map_x += ray.step_x;
			ray.side = 0;
		}
		else
		{
			ray.side_dist_y += ray.delta_dist_y;
			ray.map_y += ray.step_y;
			ray.side = 1;
		}
		if (map->grid[ray.map_y][ray.map_x] == '1')
		{
			float perpWallDist;
			if (ray.side == 0)
				perpWallDist = (ray.side_dist_x - ray.delta_dist_x);
			else
				perpWallDist = (ray.side_dist_y - ray.delta_dist_y);
			perpWallDist *= cos(angle - config->player.angle);
			calculate_draw_parameters(window_height, perpWallDist, lineHeight, drawStart, drawEnd);
			return true;
		}
	}
	return false;
}

// void render_scene(mlx_t *mlx, t_map *map, t_config *config, int window_height)
// {
// 	int		lineHeight;
// 	int		drawStart;
// 	int		drawEnd;
// 	int		x;
// 	int		y;
	
// 	clear_image(config, 0x000000);
// 	x = 0;
// 	 while (x < WINDOW_WIDTH)
//     {
//         if (cast_ray(config->player.x, config->player.y, config->player.angle + (x - WINDOW_WIDTH / 2) * (FOV / window_height), window_height, &lineHeight, &drawStart, &drawEnd, map, config))
//         {
//             y = 0;
//             while (y < drawStart)
//             {
//                 mlx_put_pixel(config->resources.images[0], x, y, 0x89CFF3FF);
//                 y++;
//             }
// 			if (config->use_textures)
//             	draw_vertical_line(config->resources.images[0], x, drawStart, drawEnd, 0xFFFFFF);
//             y = drawEnd;
//             while (y < window_height)
//             {
//                 mlx_put_pixel(config->resources.images[0], x, y, 0xB99470FF);
//                 y++;
//             }
//         }
//         x++;
// 		//    else
//         //     {
//         //         // Use wall color instead of texture
//         //         while (y < drawEnd)
//         //         {
//         //             mlx_put_pixel(config->resources.images[0], x, y, 0xB99470FF);
//         //             y++;
//         //         }
//         //     }
//         //     y = drawEnd;
//         //     while (y < window_height)
//         //     {
//         //         mlx_put_pixel(config->resources.images[0], x, y, 0xB99470FF);
//         //         y++;
//         //     }
//         // }
//         // x++;
// 	}
// 	mlx_image_to_window(mlx, config->resources.images[0], 0, 0);
// }

void render_scene(mlx_t *mlx, t_map *map, t_config *config, int window_height)
{
    int lineHeight;
    int drawStart;
    int drawEnd;
    int x;
    int y;

	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~player x %d player y %d\n", config->player.x, config->player.y);
    clear_image(config, 0x000000); // Clear the image with a black color
    x = 0;
    while (x < WINDOW_WIDTH)
    {
        if (cast_ray(config->player.x, config->player.y, config->player.angle + (x - WINDOW_WIDTH / 2) * (FOV / window_height), window_height, &lineHeight, &drawStart, &drawEnd, map, config))
        {
            y = 0;
            while (y < drawStart)
            {
                mlx_put_pixel(config->resources.images[0], x, y, 0x89CFF3FF); // Sky color
                y++;
            }
            if (config->use_textures)
            {
                draw_vertical_line(config->resources.images[0], x, drawStart, drawEnd, 0xFFFFFF); // Wall texture
            }
            else
            {
                while (y < drawEnd)
                {
                    mlx_put_pixel(config->resources.images[0], x, y, 0xFFFFFF); // Wall color
                    y++;
                }
            }
            y = drawEnd;
            while (y < window_height)
            {
                mlx_put_pixel(config->resources.images[0], x, y, 0xB99470FF); // Floor color
                y++;
            }
        }
        x++;
    }
    mlx_image_to_window(mlx, config->resources.images[0], 0, 0);
}