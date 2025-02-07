/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:52:30 by pwojnaro          #+#    #+#             */
/*   Updated: 2025/02/07 18:53:04 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

uint32_t	get_texture_pixel(mlx_image_t *texture, int x, int y);

void	draw_square(mlx_image_t *img, t_square square)
{
	int	i;
	int	j;

	i = 0;
	while (i < square.size)
	{
		j = 0;
		while (j < square.size)
		{
			mlx_put_pixel(img, square.x + i, square.y + j, square.color);
			j++;
		}
		i++;
	}
}

void	draw_minimap_in_main_image(mlx_image_t *main_img,
	mlx_image_t *minimap_img, int pos_x, int pos_y)
{
	int			x;
	int			y;
	uint32_t	color;
	int			minimap_width;
	int			minimap_height;

	minimap_width = minimap_img->width;
	minimap_height = minimap_img->height;
	if ((uint32_t)(pos_x + minimap_width) > main_img->width
	|| (uint32_t)(pos_y + minimap_height) > main_img->height)
	{
		return ;
	}
	y = 0;
	while (y < minimap_height)
	{
		x = 0;
		while (x < minimap_width)
		{
			color = get_texture_pixel(minimap_img, x, y);
			mlx_put_pixel(main_img, pos_x + x, pos_y + y, color);
			x++;
		}
		y++;
	}
}

void	draw_player_on_minimap(mlx_image_t *minimap_img, t_config *config)
{
	t_square	square;
	float		angle;
	float		player_x;
	float		player_y;
	int			size;

	angle = config->player.angle;
	player_x = config->player.x * 20;
	player_y = config->player.y * 20;
	size = 15;
	while (size--)
	{
		square.x = player_x + size * cosf(angle);
		square.y = player_y + size * sinf(angle);
		square.size = 2;
		square.color = 0x1B10B2FF;
		draw_square(minimap_img, square);
	}
	square.x = player_x - 4;
	square.y = player_y - 4;
	square.size = 10;
	square.color = 0x6EFA3AFF;
	draw_square(minimap_img, square);
}

void	render_minimap(t_minimap_render render)
{
	draw_minimap_in_main_image(render.config->img, render.minimap_img,
		render.pos_x, render.pos_y);
	mlx_delete_image(render.mlx, render.minimap_img);
	mlx_image_to_window(render.mlx, render.config->img, 0, 0);
}

void	draw_minimap(mlx_t *mlx, t_config *config, int pos_x, int pos_y)
{
	int					minimap_width;
	int					minimap_height;
	mlx_image_t			*minimap_img;
	t_minimap_render	render;

	minimap_width = config->map.width * 20;
	minimap_height = config->map.height * 20;
	minimap_img = create_minimap_image(mlx, minimap_width, minimap_height);
	if (!minimap_img)
		return ;
	draw_map_grid(minimap_img, config);
	draw_player_on_minimap(minimap_img, config);
	render.mlx = mlx;
	render.config = config;
	render.minimap_img = minimap_img;
	render.pos_x = pos_x;
	render.pos_y = pos_y;
	render_minimap(render);
}
