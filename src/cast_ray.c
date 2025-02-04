/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:04:50 by pwojnaro          #+#    #+#             */
/*   Updated: 2025/02/04 19:11:26 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	render_scene(t_render_data *data, int window_height)
{
	t_draw_params	params;
	t_texture_data	tex_data;
	int				x;
	float			ray_angle;
	int				hit_side;
	int 			y;

	clear_image(data->img, 0x000000);
	x = 0;
	while (x < WINDOW_WIDTH)
	{
		ray_angle = data->config->player.angle + (x - WINDOW_WIDTH / 2)
			* (FOV / WINDOW_WIDTH);
		if (cast_ray(data->config->player.x, data->config->player.y, ray_angle,
				window_height, &params.lineheight, &params.drawstart,
				&params.drawend, &tex_data.wallx, &hit_side, data->map,
				data->config))
		{
			y = 0;
			while (y < params.drawstart)
			{
				mlx_put_pixel(data->img, x, y, 0x89CFF3FF);
				y++;
			}
			if (data->config->use_textures)
			{
				tex_data.texture = (hit_side == 0) ? data->config->resources.images[0] : data->config->resources.images[1];
				tex_data.tex_width = tex_data.texture->width;
				tex_data.tex_height = tex_data.texture->height;
				draw_textured_vertical_line(data->img, x, &params, &tex_data);
			}
			else
			{
				draw_vertical_line(data->img, x, params.drawstart,
					params.drawend, 0xFFFFFF);
			}
			y = params.drawend;
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
