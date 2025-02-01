/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:33:24 by kkaratsi          #+#    #+#             */
/*   Updated: 2025/02/01 12:41:58 by pwojnaro         ###   ########.fr       */
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

void calculate_draw_parameters(int h, float perpWallDist, int *lineHeight, int *drawStart, int *drawEnd)
{
    // Clamp perpWallDist to a minimum positive value to avoid division by zero
    if (perpWallDist <= 0.0f) {
        perpWallDist = 0.0001f; // Small epsilon to prevent division issues
    }

    // Calculate lineHeight based on the perpendicular wall distance
    *lineHeight = (int)(h / perpWallDist);

    // Clamp lineHeight to prevent overflow or invalid values
    if (*lineHeight < 1) {
        *lineHeight = 1; // Ensure lineHeight is at least 1 pixel
    }
    if (*lineHeight > h * 10) { // Prevent excessively large values
        *lineHeight = h * 10;
    }

    // Calculate drawStart and drawEnd (vertical slice of the wall to draw)
    *drawStart = -(*lineHeight) / 2 + h / 2;
    if (*drawStart < 0) {
        *drawStart = 0; // Clamp to the top of the screen
    }

    *drawEnd = (*lineHeight) / 2 + h / 2;
    if (*drawEnd >= h) {
        *drawEnd = h - 1; // Clamp to the bottom of the screen
    }

    // Debugging output (optional)
    printf("Line height: %d, drawStart: %d, drawEnd: %d\n", *lineHeight, *drawStart, *drawEnd);
}

// bool cast_ray(float start_x, float start_y, float angle, int window_height, int *lineHeight, int *drawStart, int *drawEnd, t_map *map, t_config *config)
// {
// 	t_ray	ray;

// 	//  float ray_dir_x = cos(angle);
//     // float ray_dir_y = sin(angle);
// 	ray.map_x = (int)start_x;
// 	ray.map_y = (int)start_y;
// 	ray.delta_dist_x = fabs(1 / cos(angle));
// 	ray.delta_dist_y = fabs(1 / sin(angle));
// 	// ray.delta_dist_x = fabs(1 / ray_dir_x);
// 	// ray.delta_dist_y = fabs(1 / ray_dir_y);
// 	if (angle > 3.14159)
// 	// if (ray_dir_x < 0)
// 	{
// 		ray.step_x = -1;
// 		ray.side_dist_x = (start_x - ray.map_x) * ray.delta_dist_x;
// 	}
// 	else
// 	{
// 		ray.step_x = 1;
// 		ray.side_dist_x = (ray.map_x + 1.0 - start_x) * ray.delta_dist_x;
// 	}
// 	if (angle > 1.5708 && angle < 4.71239)
// 	// if (ray_dir_y < 0)
// 	{
// 		ray.step_y = -1;
// 		ray.side_dist_y = (start_y - ray.map_y) * ray.delta_dist_y;
// 	}
// 	else
// 	{
// 		ray.step_y = 1;
// 		ray.side_dist_y = (ray.map_y + 1.0 - start_y) * ray.delta_dist_y;
// 	}
// 	while (ray.map_y >= 0 && ray.map_y < WINDOW_HEIGHT && ray.map_x >= 0 && ray.map_x < WINDOW_WIDTH)
// 	{
// 		if (ray.side_dist_x < ray.side_dist_y)
// 		{
// 			ray.side_dist_x += ray.delta_dist_x;
// 			ray.map_x += ray.step_x;
// 			ray.side = 0;
// 		}
// 		else
// 		{
// 			ray.side_dist_y += ray.delta_dist_y;
// 			ray.map_y += ray.step_y;
// 			ray.side = 1;
// 		}
// 		if (map->grid[ray.map_y][ray.map_x] == '1')
// 		{
// 			float perpWallDist;
// 			if (ray.side == 0)
// 				perpWallDist = (ray.side_dist_x - ray.delta_dist_x);
// 			else
// 				perpWallDist = (ray.side_dist_y - ray.delta_dist_y);
// 			perpWallDist *= cos(angle - config->player.angle);
// 			calculate_draw_parameters(window_height, perpWallDist, lineHeight, drawStart, drawEnd);
// 			return true;
// 		}
// 	}
// 	return false;
// }
// 

// bool cast_ray(float start_x, float start_y, float angle, int h, int *lineHeight, int *drawStart, int *drawEnd, t_map *map, t_config *config)
// {
//     float ray_dir_x = cos(angle);
//     float ray_dir_y = sin(angle);

//     // Fix division by zero
//     float delta_dist_x = (ray_dir_x == 0) ? 1e30 : fabs(1 / ray_dir_x);
//     float delta_dist_y = (ray_dir_y == 0) ? 1e30 : fabs(1 / ray_dir_y);

//     float side_dist_x, side_dist_y;
//     int step_x, step_y;
//     int map_x = (int)start_x;
//     int map_y = (int)start_y;
//     int side;

//     if (ray_dir_x < 0)
//     {
//         step_x = -1;
//         side_dist_x = (start_x - map_x) * delta_dist_x;
//     }
//     else
//     {
//         step_x = 1;
//         side_dist_x = (map_x + 1.0 - start_x) * delta_dist_x;
//     }

//     if (ray_dir_y < 0)
//     {
//         step_y = -1;
//         side_dist_y = (start_y - map_y) * delta_dist_y;
//     }
//     else
//     {
//         step_y = 1;
//         side_dist_y = (map_y + 1.0 - start_y) * delta_dist_y;
//     }

//     while (map_x >= 0 && map_x < map->width && map_y >= 0 && map_y < map->height)
//     {
//         if (side_dist_x < side_dist_y)
//         {
//             side_dist_x += delta_dist_x;
//             map_x += step_x;
//             side = 0;
//         }
//         else
//         {
//             side_dist_y += delta_dist_y;
//             map_y += step_y;
//             side = 1;
//         }

//         if (map->grid[map_y][map_x] == '1') // Wall detected
//         {
//             float perpWallDist;
//             if (side == 0)
//                 perpWallDist = fmax((side_dist_x - delta_dist_x), 0.0001);
//             else
//                 perpWallDist = fmax((side_dist_y - delta_dist_y), 0.0001);

//             // Correct the fish-eye effect using player's angle
//             perpWallDist *= cos(angle - config->player.angle);

//             calculate_draw_parameters(h, perpWallDist, lineHeight, drawStart, drawEnd);
//             return true;
//         }
//     }
//     return false;
// }

bool cast_ray(float start_x, float start_y, float angle, int h,
              int *lineHeight, int *drawStart, int *drawEnd,
              t_map *map, t_config *config)
{
    float ray_dir_x = cosf(angle);
    float ray_dir_y = sinf(angle);

    // Prevent division by zero
    float delta_dist_x = (ray_dir_x == 0.0f) ? 1e30f : fabsf(1.0f / ray_dir_x);
    float delta_dist_y = (ray_dir_y == 0.0f) ? 1e30f : fabsf(1.0f / ray_dir_y);

    float side_dist_x;
    float side_dist_y;
    int step_x;
    int step_y;
    int map_x = (int)start_x;
    int map_y = (int)start_y;
    int side;

    // Calculate step_x and initial side_dist_x
    if (ray_dir_x < 0.0f)
    {
        step_x = -1;
        side_dist_x = (start_x - map_x) * delta_dist_x;
    }
    else
    {
        step_x = 1;
        side_dist_x = ((float)map_x + 1.0f - start_x) * delta_dist_x;
    }

    // Calculate step_y and initial side_dist_y
    if (ray_dir_y < 0.0f)
    {
        step_y = -1;
        side_dist_y = (start_y - map_y) * delta_dist_y;
    }
    else
    {
        step_y = 1;
        side_dist_y = ((float)map_y + 1.0f - start_y) * delta_dist_y;
    }

    // Ray-casting loop
    while (true)
    {
        // Move to the next map square in X or Y direction
        if (side_dist_x < side_dist_y)
        {
            side_dist_x += delta_dist_x;
            map_x += step_x;
            side = 0;
        }
        else
        {
            side_dist_y += delta_dist_y;
            map_y += step_y;
            side = 1;
        }

        // 1) Check boundaries immediately after incrementing
        // If out of bounds, break so we don't index out-of-range
        if (map_x < 0 || map_x >= map->width || map_y < 0 || map_y >= map->height)
            break;

        // 2) Now it's safe to index into the map
        if (map->grid[map_y][map_x] == '1') // a wall hit
        {
            float perpWallDist = 0.0001f; // small default to avoid zero

            if (side == 0)
                perpWallDist = fmaxf(side_dist_x - delta_dist_x, 0.0001f);
            else
                perpWallDist = fmaxf(side_dist_y - delta_dist_y, 0.0001f);

            // Correct fish-eye
            perpWallDist *= cosf(angle - config->player.angle);

            // Calculate drawing parameters
            calculate_draw_parameters(h, perpWallDist, lineHeight, drawStart, drawEnd);
            return true;
        }
    }
    // If we exit the loop, no wall was hit within bounds
    return false;
}

void render_scene(mlx_t *mlx, t_map *map, t_config *config, int window_height)
{
    int lineHeight;
    int drawStart;
    int drawEnd;
    int x;
    int y;

	mlx_image_t *img = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
    clear_image(img, 0x000000); // Clear the image with a black color
    x = 0;
    while (x < WINDOW_WIDTH)
    {
        if (cast_ray(config->player.x, config->player.y, config->player.angle + (x - WINDOW_WIDTH / 2) * (FOV / window_height), window_height, &lineHeight, &drawStart, &drawEnd, map, config))
        {
            y = 0;
            while (y < drawStart)
            {
                mlx_put_pixel(img, x, y, 0x89CFF3FF); // Sky color
                y++;
            }
            draw_vertical_line(img, x, drawStart, drawEnd, 0xFFFFFF); // Wall texture
            y = drawEnd;
            while (y < WINDOW_HEIGHT)
            {
                mlx_put_pixel(img, x, y, 0xB99470FF); // Floor color
                y++;
            }
        }
        x++;
    }
    mlx_image_to_window(mlx, img, 0, 0);
}
