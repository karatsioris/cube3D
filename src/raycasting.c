/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:33:24 by kkaratsi          #+#    #+#             */
/*   Updated: 2025/02/04 19:13:11 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

uint32_t	convert_abgr_to_rgba(uint32_t abgr)
{
	uint32_t	a;
	uint32_t	b;
	uint32_t	g;
	uint32_t	r;

	a = (abgr & 0xFF000000);
	b = (abgr & 0x00FF0000) >> 16;
	g = (abgr & 0x0000FF00);
	r = (abgr & 0x000000FF) << 16;
	return (a | r | g | b);
}

uint32_t	get_texture_pixel(mlx_image_t *texture, int x, int y)
{
	uint32_t const	*pixels = (uint32_t *)texture->pixels;
	int				index;
	uint32_t		color;

	index = y * texture->width + x;
	color = pixels[index];
	color = convert_abgr_to_rgba(color);
	color |= 0xFF000000;
	return (color);
}

void	draw_vertical_line(mlx_image_t *img, int x, int drawStart, int drawEnd,
	uint32_t color)
{
	int	y;

	y = drawStart;
	while (y < drawEnd)
	{
		mlx_put_pixel(img, x, y, color);
		y++;
	}
}

void	draw_textured_vertical_line(mlx_image_t *img, int x,
	t_draw_params *params, t_texture_data *tex_data)
{
	int			tex_x;
	float		step;
	float		tex_pos;
	int			y;
	int			tex_y;
	uint32_t	color;

	tex_x = (int)(tex_data->wallx * (float)tex_data->tex_width);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= tex_data->tex_width)
		tex_x = tex_data->tex_width - 1;
	step = (float)tex_data->tex_height / (params->drawend - params->drawstart);
	tex_pos = 0;
	y = params->drawstart;
	while (y < params->drawend)
	{
		tex_y = (int)tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= tex_data->tex_height)
			tex_y = tex_data->tex_height - 1;
		color = get_texture_pixel(tex_data->texture, tex_x, tex_y);
		mlx_put_pixel(img, x, y, color);
		tex_pos += step;
		y++;
	}
}

void	calculate_draw_parameters(int h, float perpWallDist,
	t_draw_params *params)
{
	if (perpWallDist <= 0.0f)
		perpWallDist = 0.0001f;
	params->lineheight = (int)(h / perpWallDist);
	if (params->lineheight < 1)
		params->lineheight = 1;
	if (params->lineheight > h * 10)
		params->lineheight = h * 10;
	params->drawstart = -(params->lineheight) / 2 + h / 2;
	if (params->drawstart < 0)
		params->drawstart = 0;
	params->drawend = (params->lineheight) / 2 + h / 2;
	if (params->drawend >= h)
		params->drawend = h - 1;
}

bool cast_ray(float start_x, float start_y, float angle, int h,
	int *lineHeight, int *drawStart, int *drawEnd, float *wallX, int *hit_side,
	t_map *map, t_config *config)
{
	float	hit;
	float	perpwalldist;
	float	ray_dir_x = cosf(angle);
	float	ray_dir_y = sinf(angle);
	float	delta_dist_x = (ray_dir_x == 0.0f) ? 1e30f : fabsf(1.0f / ray_dir_x);
	float	delta_dist_y = (ray_dir_y == 0.0f) ? 1e30f : fabsf(1.0f / ray_dir_y);
	float	side_dist_x;
	float	side_dist_y;
	int		step_x;
	int		step_y;
	int		map_x = (int)start_x;
	int		map_y = (int)start_y;
	int		side;

	if (fabsf(start_x - map_x) < 1e-6f)
		start_x = map_x;
	if (fabsf(start_y - map_y) < 1e-6f)
		start_y = map_y;
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
		if (side_dist_x < side_dist_y || (side_dist_x == side_dist_y
				&& ray_dir_x < 0))
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
		if (map_x < 0 || map_x >= map->width || map_y < 0
			|| map_y >= map->height)
		{
			printf("[DEBUG] Ray went out of bounds.\n");
			break ;
		}
		if (map->grid[map_y][map_x] == '1')
		{
			if (side == 0)
				perpwalldist = fmaxf(side_dist_x - delta_dist_x, 0.0001f);
			else
				perpwalldist = fmaxf(side_dist_y - delta_dist_y, 0.0001f);
			perpwalldist *= cosf(angle - config->player.angle);
			t_draw_params params;
			calculate_draw_parameters(h, perpwalldist, &params);
			*lineHeight = params.lineheight;
			*drawStart = params.drawstart;
			*drawEnd = params.drawend;
			if (side == 0)
			{
				hit = start_y + perpwalldist * ray_dir_y;
				*wallX = hit - floorf(hit);
				if (ray_dir_x > 0)
					*wallX = 1.0f - *wallX;
			}
			else
			{
				hit = start_x + perpwalldist * ray_dir_x;
				*wallX = hit - floorf(hit);
				if (ray_dir_y < 0)
					*wallX = 1.0f - *wallX;
			}
			*wallX = fmaxf(0.0f, fminf(*wallX, 1.0f));
			*hit_side = side;
			return (true);
		}
	}
	return (false);
}
