/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaratsi <kkaratsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:33:24 by kkaratsi          #+#    #+#             */
/*   Updated: 2025/02/07 16:58:09 by kkaratsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	draw_vertical_line(mlx_image_t *img, int x, t_draw_params *params,
	uint32_t color)
{
	int	y;

	y = params->drawstart;
	while (y < params->drawend )
	{
		mlx_put_pixel(img, x, y, color);
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
	if (params->lineheight > h) // maybe this should be h * 10
		params->lineheight = h;
	params->drawstart = -(params->lineheight) / 2 + h / 2;
	if (params->drawstart < 0)
		params->drawstart = 0;
	params->drawend = (params->lineheight) / 2 + h / 2;
	if (params->drawend >= h)
		params->drawend = h - 1;
}

// bool	cast_ray(t_cast_data *data)
// {
// 	float	hit;
// 	float	perpwalldist;
// 	float	ray_dir_x = cosf(data->angle);
// 	float	ray_dir_y = sinf(data->angle);
// 	float	delta_dist_x = (ray_dir_x == 0.0f) ? 1e30f : fabsf(1.0f / ray_dir_x);
// 	float	delta_dist_y = (ray_dir_y == 0.0f) ? 1e30f : fabsf(1.0f / ray_dir_y);
// 	float	side_dist_x;
// 	float	side_dist_y;
// 	int		step_x;
// 	int		step_y;
// 	int		map_x = (int)data->start_x;
// 	int		map_y = (int)data->start_y;
// 	int		side;

// 	if (fabsf(data->start_x - map_x) < 1e-6f)
// 		data->start_x = map_x;
// 	if (fabsf(data->start_y - map_y) < 1e-6f)
// 		data->start_y = map_y;
// 	if (ray_dir_x < 0.0f)
// 	{
// 		step_x = -1;
// 		side_dist_x = (data->start_x - map_x) * delta_dist_x;
// 	}
// 	else
// 	{
// 		step_x = 1;
// 		side_dist_x = ((float)map_x + 1.0f - data->start_x) * delta_dist_x;
// 	}
// 	if (ray_dir_y < 0.0f)
// 	{
// 		step_y = -1;
// 		side_dist_y = (data->start_y - map_y) * delta_dist_y;
// 	}
// 	else
// 	{
// 		step_y = 1;
// 		side_dist_y = ((float)map_y + 1.0f - data->start_y) * delta_dist_y;
// 	}
// 	while (true)
// 	{
// 		if (side_dist_x < side_dist_y)
// 		{
// 			side_dist_x += delta_dist_x;
// 			map_x += step_x;
// 			side = 0;
// 			// side = (step_x > 0) ? 0 : 1; // 0: right, 1: left

// 		}
// 		else
// 		{
// 			side_dist_y += delta_dist_y;
// 			map_y += step_y;
// 			// side = 1;
// 			side = (step_y > 0) ? 2 : 3; // 2: top, 3: bottom
// 		}
// 		if (map_x < 0 || map_x >= data->map->width || map_y < 0
// 			|| map_y >= data->map->height)
// 		{
// 			printf("[DEBUG] Ray went out of bounds.\n");
// 			break ;
// 		}
// 		if (data->map->grid[map_y][map_x] == '1')
// 		{
// 			if (side == 0)
// 				perpwalldist = fmaxf(side_dist_x - delta_dist_x, 0.0001f);
// 			else
// 				perpwalldist = fmaxf(side_dist_y - delta_dist_y, 0.0001f);
// 			perpwalldist *= cosf(data->angle - data->config->player.angle);
// 			data->ray.draw_params.lineheight = 0;
// 			data->ray.draw_params.drawstart = 0;
// 			data->ray.draw_params.drawend = 0;
// 			calculate_draw_parameters(data->h, perpwalldist,
// 				&data->ray.draw_params);
// 			if (side == 0) // hit a vertical wall
// 			{
// 				hit = data->start_y + perpwalldist * ray_dir_y;
// 				data->ray.wallx = hit - floorf(hit);
// 				if (ray_dir_x > 0) 
// 					data->ray.wallx = 1.0f - data->ray.wallx;
// 			}
// 			else // hit a horizontal wall
// 			{
// 				hit = data->start_x + perpwalldist * ray_dir_x;
// 				data->ray.wallx = hit - floorf(hit);
// 				if (ray_dir_y < 0)
// 					data->ray.wallx = 1.0f - data->ray.wallx;
// 			}
// 			data->ray.wallx = fmaxf(0.0f, fminf(data->ray.wallx, 1.0f));
// 			data->ray.hit_side = side;
// 			// data->ray.texture = data->resources->images[side];
// 	// 		printf("[DEBUG] Ray Hit: Side = %d, WallX = %f, RayDirX = %f, RayDirY = %f\n",
//     //    data->ray.hit_side, data->ray.wallx, ray_dir_x, ray_dir_y);

// 			return (true);
// 		}
// 	}
// 	return (false);
// }

bool	cast_ray(t_cast_data *data)
{
	float	hit;
	float	perpwalldist;
	float	ray_dir_x = cosf(data->angle);
	float	ray_dir_y = sinf(data->angle);
	float	delta_dist_x = (ray_dir_x == 0.0f) ? 1e30f : fabsf(1.0f / ray_dir_x);
	float	delta_dist_y = (ray_dir_y == 0.0f) ? 1e30f : fabsf(1.0f / ray_dir_y);
	float	side_dist_x;
	float	side_dist_y;
	int		step_x;
	int		step_y;
	int		map_x = (int)data->start_x;
	int		map_y = (int)data->start_y;
	int		side;

	if (fabsf(data->start_x - map_x) < 1e-6f)
		data->start_x = map_x;
	if (fabsf(data->start_y - map_y) < 1e-6f)
		data->start_y = map_y;
	if (ray_dir_x < 0.0f)
	{
		step_x = -1;
		side_dist_x = (data->start_x - map_x) * delta_dist_x;
	}
	else
	{
		step_x = 1;
		side_dist_x = ((float)map_x + 1.0f - data->start_x) * delta_dist_x;
	}
	if (ray_dir_y < 0.0f)
	{
		step_y = -1;
		side_dist_y = (data->start_y - map_y) * delta_dist_y;
	}
	else
	{
		step_y = 1;
		side_dist_y = ((float)map_y + 1.0f - data->start_y) * delta_dist_y;
	}
	while (true)
	{
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			map_x += step_x;
			// side = 0;
			side = (step_x > 0) ? 0 : 1; // 0: right, 1: left

		}
		else
		{
			side_dist_y += delta_dist_y;
			map_y += step_y;
			// side = 1;
			side = (step_y > 0) ? 2 : 3; // 2: top, 3: bottom
		}
		if (map_x < 0 || map_x >= data->map->width || map_y < 0
			|| map_y >= data->map->height)
		{
			printf("[DEBUG] Ray went out of bounds.\n");
			break ;
		}
		if (data->map->grid[map_y][map_x] == '1')
		{
			if (side == 0 || side == 1)
				perpwalldist = fmaxf(side_dist_x - delta_dist_x, 0.0001f);
			else
				perpwalldist = fmaxf(side_dist_y - delta_dist_y, 0.0001f);	
			perpwalldist *= cosf(data->angle - data->config->player.angle);
			data->ray.draw_params.lineheight = 0;
			data->ray.draw_params.drawstart = 0;
			data->ray.draw_params.drawend = 0;
			calculate_draw_parameters(data->h, perpwalldist,
				&data->ray.draw_params);
			if (side == 0 || side == 1) // hit a vertical wall
			{
				hit = data->start_y + perpwalldist * ray_dir_y;
				data->ray.wallx = hit - floorf(hit);
				if (ray_dir_x > 0) 
					data->ray.wallx = 1.0f - data->ray.wallx;
			}
			else // hit a horizontal wall
			{
				hit = data->start_x + perpwalldist * ray_dir_x;
				data->ray.wallx = hit - floorf(hit);
				if (ray_dir_y < 0)
					data->ray.wallx = 1.0f - data->ray.wallx;
			}
			data->ray.wallx = fmaxf(0.0f, fminf(data->ray.wallx, 1.0f));
			data->ray.hit_side = side;
			return (true);
		}
	}
	return (false);
}


