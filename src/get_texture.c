/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:18:58 by pwojnaro          #+#    #+#             */
/*   Updated: 2025/02/08 13:00:20 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "raycaster.h"

uint32_t	convert_abgr_to_rgba(uint32_t abgr)
{
	uint32_t	a;
	uint32_t	b;
	uint32_t	g;
	uint32_t	r;

	a = (abgr & 0xFF000000) >> 24;
	b = (abgr & 0x00FF0000) >> 8;
	g = (abgr & 0x0000FF00) << 8;
	r = (abgr & 0x000000FF) << 24;
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
	return (color);
}

int	get_texture_x(t_texture_data *tex_data)
{
	int	tex_x;

	tex_x = (int)(tex_data->wallx * (float)tex_data->tex_width);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= tex_data->tex_width)
		tex_x = tex_data->tex_width - 1;
	return (tex_x);
}

int	get_texture_y(float tex_pos, int tex_height)
{
	int	tex_y;

	tex_y = (int)tex_pos;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= tex_height)
		tex_y = tex_height - 1;
	return (tex_y);
}

void	draw_textured_vertical_line(mlx_image_t *img, int x,
	t_draw_params *params, t_texture_data *tex_data)
{
	int		tex_x;
	int		tex_y;
	float	tex_pos;
	float	step;
	int		y;

	tex_x = get_texture_x(tex_data);
	step = (float)tex_data->tex_height / (float)(params->lineheight);
	tex_pos = (params->drawstart - (WINDOW_HEIGHT / 2)
			+ (params->lineheight / 2)) * step;
	y = params->drawstart;
	while (y < params->drawend)
	{
		tex_y = get_texture_y(tex_pos, tex_data->tex_height);
		mlx_put_pixel(img, x, y, get_texture_pixel(tex_data->texture,
				tex_x, tex_y));
		tex_pos += step;
		y++;
	}
}
