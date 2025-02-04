/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:04:50 by pwojnaro          #+#    #+#             */
/*   Updated: 2025/02/04 20:47:01 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	render_scene(t_render_data *data, int window_height)
{
	t_cast_data		cast_data;
	t_texture_data	tex_data;
	int				x;
	float			ray_angle;
	int				y;

	clear_image(data->img, 0x000000);
	x = 0;
	while (x < WINDOW_WIDTH)
	{
		ray_angle = data->config->player.angle + (x - WINDOW_WIDTH / 2)
			* (FOV / WINDOW_WIDTH);
		cast_data.start_x = data->config->player.x;
		cast_data.start_y = data->config->player.y;
		cast_data.angle = ray_angle;
		cast_data.h = window_height;
		cast_data.map = data->map;
		cast_data.config = data->config;
		cast_data.ray.draw_params.lineheight = 0;
		cast_data.ray.draw_params.drawstart = 0;
		cast_data.ray.draw_params.drawend = 0;
		cast_data.ray.wallx = 0.0f;
		cast_data.ray.hit_side = 0;
		if (cast_ray(&cast_data))
		{
			y = 0;
			while (y < cast_data.ray.draw_params.drawstart)
			{
				mlx_put_pixel(data->img, x, y, 0x89CFF3FF);
				y++;
			}
			if (data->config->use_textures)
			{
				tex_data.texture = (cast_data.ray.hit_side == 0)
					? data->config->resources.images[0]
					: data->config->resources.images[1];
				tex_data.tex_width = tex_data.texture->width;
				tex_data.tex_height = tex_data.texture->height;
				tex_data.wallx = cast_data.ray.wallx;
				draw_textured_vertical_line(data->img, x,
					&cast_data.ray.draw_params, &tex_data);
			}
			else
			{
				draw_vertical_line(data->img, x, &cast_data.ray.draw_params,
					0xFFFFFF);
			}
			y = cast_data.ray.draw_params.drawend;
			while (y < WINDOW_HEIGHT)
			{
				mlx_put_pixel(data->img, x, y, 0xB99470FF);
				y++;
			}
		}
		x++;
	}
	mlx_image_to_window(data->mlx, data->img, 0, 0);
}
