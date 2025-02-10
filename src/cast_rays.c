/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:53:05 by pwojnaro          #+#    #+#             */
/*   Updated: 2025/02/10 13:40:22 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"

void	compute_wall_hit(t_cast_data *data, t_ray_calc *calc,
	float perpwalldist)
{
	float	hit;

	if (calc->side == 0)
	{
		hit = data->start_y + perpwalldist * calc->ray_dir_y;
		data->ray.wallx = hit - floorf(hit);
		if (calc->ray_dir_x > 0.0f)
			data->ray.wallx = 1.0f - data->ray.wallx;
	}
	else
	{
		hit = data->start_x + perpwalldist * calc->ray_dir_x;
		data->ray.wallx = hit - floorf(hit);
		if (calc->ray_dir_y < 0.0f)
			data->ray.wallx = 1.0f - data->ray.wallx;
	}
	if (data->ray.wallx < 0.0f)
		data->ray.wallx = 0.0f;
	else if (data->ray.wallx > 1.0f)
		data->ray.wallx = 1.0f;
}

static inline void	adjust_start(float *start, int map)
{
	if (fabsf(*start - (float)map) < 1e-6f)
		*start = (float)map;
}

static inline float	calc_delta_dist(float ray_dir)
{
	if (ray_dir == 0.0f)
		return (1e30f);
	return (fabsf(1.0f / ray_dir));
}

bool	cast_ray(t_cast_data *data)
{
	t_ray_calc	calc;
	float		perpwalldist;

	calc.ray_dir_x = cosf(data->angle);
	calc.ray_dir_y = sinf(data->angle);
	calc.map_x = (int)data->start_x;
	calc.map_y = (int)data->start_y;
	adjust_start(&data->start_x, calc.map_x);
	adjust_start(&data->start_y, calc.map_y);
	calc.delta_dist_x = calc_delta_dist(calc.ray_dir_x);
	calc.delta_dist_y = calc_delta_dist(calc.ray_dir_y);
	init_step_and_side_distances(data, &calc);
	if (!perform_dda(data, &calc))
		return (false);
	perpwalldist = compute_perpwalldist(data, &calc);
	calculate_draw_parameters(data->h, perpwalldist, &data->ray.draw_params);
	compute_wall_hit(data, &calc, perpwalldist);
	data->ray.hit_side = calc.side;
	return (true);
}

int	create_rgb(int color[3])
{
	return ((color[0] << 24) | (color[1] << 16) | (color[2] << 8) | 0xFF);
}
