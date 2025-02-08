/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:33:24 by kkaratsi          #+#    #+#             */
/*   Updated: 2025/02/06 15:01:42 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	draw_vertical_line(mlx_image_t *img, int x, t_draw_params *params,
	uint32_t color)
{
	int	y;

	y = params->drawstart;
	while (y < params->drawend)
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
	if (params->lineheight > h * 10)
		params->lineheight = h * 10;
	params->drawstart = -(params->lineheight) / 2 + h / 2;
	if (params->drawstart < 0)
		params->drawstart = 0;
	params->drawend = (params->lineheight) / 2 + h / 2;
	if (params->drawend >= h)
		params->drawend = h - 1;
}

void	init_step_and_side_distances(t_cast_data *data, t_ray_calc *calc)
{
	if (calc->ray_dir_x < 0.0f)
	{
		calc->step_x = -1;
		calc->side_dist_x = (data->start_x - (float)calc->map_x)
			* calc->delta_dist_x;
	}
	else
	{
		calc->step_x = 1;
		calc->side_dist_x = (((float)calc->map_x) + 1.0f - data->start_x)
			* calc->delta_dist_x;
	}
	if (calc->ray_dir_y < 0.0f)
	{
		calc->step_y = -1;
		calc->side_dist_y = (data->start_y - (float)calc->map_y)
			* calc->delta_dist_y;
	}
	else
	{
		calc->step_y = 1;
		calc->side_dist_y = (((float)calc->map_y) + 1.0f - data->start_y)
			* calc->delta_dist_y;
	}
}

bool	perform_dda(t_cast_data *data, t_ray_calc *calc)
{
	while (true)
	{
		if (calc->side_dist_x < calc->side_dist_y)
		{
			calc->side_dist_x += calc->delta_dist_x;
			calc->map_x += calc->step_x;
			calc->side = 0;
		}
		else
		{
			calc->side_dist_y += calc->delta_dist_y;
			calc->map_y += calc->step_y;
			calc->side = 1;
		}
		if (calc->map_x < 0 || calc->map_x >= data->map->width
			|| calc->map_y < 0 || calc->map_y >= data->map->height)
		{
			printf("[DEBUG] Ray went out of bounds.\n");
			return (false);
		}
		if (data->map->grid[calc->map_y][calc->map_x] == '1')
			return (true);
	}
	return (false);
}

float	compute_perpwalldist(t_cast_data *data, t_ray_calc *calc)
{
	float	perpwalldist;

	if (calc->side == 0)
		perpwalldist = calc->side_dist_x - calc->delta_dist_x;
	else
		perpwalldist = calc->side_dist_y - calc->delta_dist_y;
	if (perpwalldist < 0.0001f)
		perpwalldist = 0.0001f;
	perpwalldist *= cosf(data->angle - data->config->player.angle);
	return (perpwalldist);
}
