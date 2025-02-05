/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 12:23:56 by piotrwojnar       #+#    #+#             */
/*   Updated: 2025/02/05 19:02:46 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	update_player_position(t_config *config, t_map *map,
	float move_distance, float angle_offset)
{
	if (can_move_forward(config, map, move_distance, angle_offset))
	{
		config->player.x += cosf(config->player.angle + angle_offset)
			* move_distance;
		config->player.y += sinf(config->player.angle + angle_offset)
			* move_distance;
	}
	else
	{
		ft_printf("[DEBUG] Movement blocked: Collision detected.\n");
	}
}

bool	is_wall(t_map *map, int x, int y)
{
	if (x < 0 || x >= map->width || y < 0 || y >= map->height)
		return (true);
	return (map->grid[y][x] == '1');
}

void	player_move_handler(mlx_key_data_t keydata, void *param)
{
	t_config	*config;
	float		move_speed;
	float		rot_speed;

	move_speed = 0.3f;
	rot_speed = 0.3f;
	config = (t_config *)param;
	if (keydata.action != MLX_PRESS && keydata.action != MLX_REPEAT)
		return ;
	if (keydata.key == MLX_KEY_W)
		update_player_position(config, &config->map, move_speed, 0.0f);
	else if (keydata.key == MLX_KEY_S)
		update_player_position(config, &config->map, move_speed, M_PI);
	else if (keydata.key == MLX_KEY_A)
		update_player_position(config, &config->map, move_speed, -M_PI_2);
	else if (keydata.key == MLX_KEY_D)
		update_player_position(config, &config->map, move_speed, M_PI_2);
	else if (keydata.key == MLX_KEY_LEFT)
		config->player.angle -= rot_speed;
	else if (keydata.key == MLX_KEY_RIGHT)
		config->player.angle += rot_speed;
}

void	clear_image(mlx_image_t *img, uint32_t color)
{
	uint32_t	y;
	uint32_t	x;

	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			mlx_put_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
}

int	main(int argc, char **argv)
{
	t_config	config = {0};
	t_memory	mem = {0};

	config.use_textures = true;
	if (!mem_init(&mem))
		return (1);
	config.memory = &mem;
	initialize_config(&config);
	if (!validate_args_and_load_map(argc, argv, &config, &mem))
		return (1);
	validate_map(&config.map);
	config.map.mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT,
			"Cube3D - Textured Walls", true);
	if (!config.map.mlx)
	{
		ft_clean(&config.map, &mem, &config.resources);
		return (1);
	}
	if (config.use_textures)
		load_textures(&config.resources, &config.textures, config.map.mlx,
			config.memory);
	else
	{
		ft_printf("[DEBUG] Skipping texture loading, using colors instead.\n");
	}
	game_loop(&config.map, &config);
	cleanup_resources(&config.resources, config.map.mlx);
	ft_clean(&config.map, &mem, &config.resources);
	return (0);
}
