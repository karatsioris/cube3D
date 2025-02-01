/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:33:24 by kkaratsi          #+#    #+#             */
/*   Updated: 2025/02/01 17:07:46 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

uint32_t get_texture_pixel(mlx_image_t *texture, int x, int y)
{
	uint32_t const *pixels = (uint32_t *)texture->pixels;
	int index = y * texture->width + x;
	return pixels[index];
}

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

void draw_textured_vertical_line(mlx_image_t *img, int x, int drawStart, int drawEnd,
								   mlx_image_t *texture, int tex_width, int tex_height, float wallX)
{
	// Calculate the corresponding x-coordinate in the texture
	int tex_x = (int)(wallX * (float)tex_width);
	if (tex_x < 0) tex_x = 0;
	if (tex_x >= tex_width) tex_x = tex_width - 1;
	
	// Calculate the step: how much to move in the texture per screen pixel in the wall slice
	float step = (float)tex_height / (drawEnd - drawStart);
	float tex_pos = 0;
	
	for (int y = drawStart; y < drawEnd; y++)
	{
		int tex_y = (int)tex_pos;
		if (tex_y < 0) tex_y = 0;
		if (tex_y >= tex_height) tex_y = tex_height - 1;
		uint32_t color = get_texture_pixel(texture, tex_x, tex_y);
		mlx_put_pixel(img, x, y, color);
		tex_pos += step;
	}
}

void calculate_draw_parameters(int h, float perpWallDist, int *lineHeight, int *drawStart, int *drawEnd)
{
	if (perpWallDist <= 0.0f)
	{
		perpWallDist = 0.0001f;
	}

	*lineHeight = (int)(h / perpWallDist);

	if (*lineHeight < 1)
	{
		*lineHeight = 1;
	}
	if (*lineHeight > h * 10)
	{
		*lineHeight = h * 10;
	}

	*drawStart = -(*lineHeight) / 2 + h / 2;
	if (*drawStart < 0)
	{
		*drawStart = 0;
	}

	*drawEnd = (*lineHeight) / 2 + h / 2;
	if (*drawEnd >= h)
	{
		*drawEnd = h - 1;
	}
}

bool cast_ray(float start_x, float start_y, float angle, int h,
			  int *lineHeight, int *drawStart, int *drawEnd, float *wallX, int *hit_side,
			  t_map *map, t_config *config)
{
	float ray_dir_x = cosf(angle);
	float ray_dir_y = sinf(angle);
	float delta_dist_x = (ray_dir_x == 0.0f) ? 1e30f : fabsf(1.0f / ray_dir_x);
	float delta_dist_y = (ray_dir_y == 0.0f) ? 1e30f : fabsf(1.0f / ray_dir_y);
	float side_dist_x;
	float side_dist_y;
	int step_x;
	int step_y;
	int map_x = (int)start_x;
	int map_y = (int)start_y;
	int side;

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
	while (true)
	{
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
		// Stop if out of bounds
		if (map_x < 0 || map_x >= map->width || map_y < 0 || map_y >= map->height)
			break;
		
		if (map->grid[map_y][map_x] == '1')
		{
			float perpWallDist;
			if (side == 0)
				perpWallDist = fmaxf(side_dist_x - delta_dist_x, 0.0001f);
			else
				perpWallDist = fmaxf(side_dist_y - delta_dist_y, 0.0001f);
			// Correct the fish-eye effect
			perpWallDist *= cosf(angle - config->player.angle);
			calculate_draw_parameters(h, perpWallDist, lineHeight, drawStart, drawEnd);
			
			// Compute the exact position of the hit on the wall (wallX)
			float hit;
			if (side == 0)
				hit = start_y + perpWallDist * ray_dir_y;
			else
				hit = start_x + perpWallDist * ray_dir_x;
			*wallX = hit - floorf(hit);
			
			*hit_side = side;
			return true;
		}
	}
	return false;
}

void render_scene(mlx_t *mlx, t_map *map, t_config *config, int window_height)
{
	int lineHeight, drawStart, drawEnd;
	int x, y;
	float wallX;
	int hit_side;

	mlx_image_t *img = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	clear_image(img, 0x000000);

	for (x = 0; x < WINDOW_WIDTH; x++)
	{
		// Compute the ray angle for this column
		float ray_angle = config->player.angle + (x - WINDOW_WIDTH / 2) * (FOV / window_height);
		if (cast_ray(config->player.x, config->player.y, ray_angle, window_height,
					 &lineHeight, &drawStart, &drawEnd, &wallX, &hit_side, map, config))
		{
			// Draw sky (above the wall)
			for (y = 0; y < drawStart; y++)
				mlx_put_pixel(img, x, y, 0x89CFF3FF); // Sky color

			// If textures are used, sample the texture; otherwise, use a flat color.
			if (config->use_textures)
			{
				// For demonstration, choose a texture based on the hit side.
				// (You can refine this logic to choose between north, south, east, and west.)
				mlx_image_t *texture_img;
				if (hit_side == 0)
				{
					// For a vertical hit, you might decide based on the ray direction.
					// Here we simply use the "north" texture.
					texture_img = config->resources.images[0]; 
				}
				else
				{
					// For a horizontal hit, for example, use the "south" texture.
					texture_img = config->resources.images[0];
				}
				// Assume texture_img is valid and has width/height properties.
				draw_textured_vertical_line(img, x, drawStart, drawEnd, texture_img,
											texture_img->width, texture_img->height, wallX);
			}
			else
			{
				draw_vertical_line(img, x, drawStart, drawEnd, 0xFFFFFF);
			}
			
			// Draw floor (below the wall)
			for (y = drawEnd; y < WINDOW_HEIGHT; y++)
				mlx_put_pixel(img, x, y, 0xB99470FF); // Floor color
		}
	}
	mlx_image_to_window(mlx, img, 0, 0);
}

