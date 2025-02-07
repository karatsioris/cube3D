/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaratsi <kkaratsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:04:50 by pwojnaro          #+#    #+#             */
/*   Updated: 2025/02/07 16:18:59 by kkaratsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	draw_ceiling_and_floor(mlx_image_t *img, int x, t_ray_data *ray)
{
	int	y;

	y = 0;
	while (y < ray->draw_params.drawstart)
	{
		mlx_put_pixel(img, x, y, 0x89CFF3FF);
		y++;
	}
	y = ray->draw_params.drawend;
	while (y < WINDOW_HEIGHT)
	{
		mlx_put_pixel(img, x, y, 0xB99470FF);
		y++;
	}
}

void	render_wall(mlx_image_t *img, int x, t_cast_data *cast_data,
	t_config *config)

{
	
	t_texture_data	tex_data;

	if (config->use_textures)
	{
		if (cast_data->ray.hit_side == 0)
			tex_data.texture = config->resources.images[0];
		else if (cast_data->ray.hit_side == 1)
			tex_data.texture = config->resources.images[1];
		else if (cast_data->ray.hit_side == 2)
			tex_data.texture = config->resources.images[2];
		else
			tex_data.texture = config->resources.images[3];
		tex_data.tex_width = tex_data.texture->width;
		tex_data.tex_height = tex_data.texture->height;
		tex_data.wallx = cast_data->ray.wallx;
		draw_textured_vertical_line(img, x, &cast_data->ray.draw_params,
			&tex_data);
	}
	else
	{
		draw_vertical_line(img, x, &cast_data->ray.draw_params, 0xFFFFFF);
	}
}

void	init_cast_data(t_cast_data *cast_data, t_render_data *data,
	float ray_angle, int window_height)
{
	cast_data->start_x = data->config->player.x;
	cast_data->start_y = data->config->player.y;
	cast_data->angle = ray_angle;
	cast_data->h = window_height;
	cast_data->map = data->map;
	cast_data->config = data->config;
	cast_data->ray.draw_params.lineheight = 0;
	cast_data->ray.draw_params.drawstart = 0;
	cast_data->ray.draw_params.drawend = 0;
	cast_data->ray.wallx = 0.0f;
	cast_data->ray.hit_side = 0;
}

void	render_scene(t_render_data *data, int window_height)
{
	t_cast_data	cast_data;
	int			x;
	float		ray_angle;

	clear_image(data->img, 0x000000);
	x = 0;
	while (x < WINDOW_WIDTH)
	{
		ray_angle = data->config->player.angle + (x - WINDOW_WIDTH / 2)
			* (FOV / WINDOW_WIDTH);
		init_cast_data(&cast_data, data, ray_angle, window_height);
		if (cast_ray(&cast_data))
		{
			draw_ceiling_and_floor(data->img, x, &cast_data.ray);
			render_wall(data->img, x, &cast_data, data->config);
		}
		x++;
	}
	draw_minimap(data->mlx, data->config, 0, 0);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
	// free(data->config->rays);
	// data->config->rays = NULL;
	// data->config->num_rays = 0;
}
