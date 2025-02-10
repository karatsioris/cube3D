/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:04:50 by pwojnaro          #+#    #+#             */
/*   Updated: 2025/02/10 13:48:26 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"

void	draw_ceiling_and_floor(mlx_image_t *img, int x, t_ray_data *ray)
{
	int	y;

	y = 0;
	while (y < ray->draw_params.drawstart)
	{
		mlx_put_pixel(img, x, y, ray->ceiling_color);
		y++;
	}
	y = ray->draw_params.drawend;
	while (y < WINDOW_HEIGHT)
	{
		mlx_put_pixel(img, x, y, ray->floor_color);
		y++;
	}
}

int	get_texture_index(t_cast_data *cast_data, float ray_dir_x, float ray_dir_y)
{
	if (cast_data->ray.hit_side == 0)
	{
		if (ray_dir_x > 0)
			return (3);
		else
			return (2);
	}
	else
	{
		if (ray_dir_y > 0)
			return (1);
		else
			return (0);
	}
}

void	render_wall(mlx_image_t *img, int x, t_cast_data *cast_data,
	t_config *config)
{
	t_texture_data	tex_data;
	float			ray_dir_x;
	float			ray_dir_y;
	int				tex_index;

	if (!config->use_textures)
	{
		draw_vertical_line(img, x, &cast_data->ray.draw_params, 0xFFFFFF);
		return ;
	}
	ray_dir_x = cosf(cast_data->angle);
	ray_dir_y = sinf(cast_data->angle);
	tex_index = get_texture_index(cast_data, ray_dir_x, ray_dir_y);
	tex_data.texture = config->resources.images[tex_index];
	tex_data.tex_width = tex_data.texture->width;
	tex_data.tex_height = tex_data.texture->height;
	tex_data.wallx = cast_data->ray.wallx;
	draw_textured_vertical_line(img, x, &cast_data->ray.draw_params, &tex_data);
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
		cast_data.ray.ceiling_color = create_rgb(data->config->colors.ceiling);
		cast_data.ray.floor_color = create_rgb(data->config->colors.floor);
		if (cast_ray(&cast_data))
		{
			draw_ceiling_and_floor(data->img, x, &cast_data.ray);
			render_wall(data->img, x, &cast_data, data->config);
		}
		x++;
	}
	draw_minimap(data->mlx, data->config, 0, 0);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
}
