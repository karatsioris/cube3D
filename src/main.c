/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 12:23:56 by piotrwojnar       #+#    #+#             */
/*   Updated: 2025/02/04 17:28:19 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#define COLLISION_MARGIN 0.1f

bool	can_move_forward(t_config *config, t_map *map, float move_distance,
	float angle_offset)
{
	int		grid_x;
	int		grid_y;
	float	new_x;
	float	new_y;
	float	frac_x;
	float	frac_y;

	new_x = config->player.x + cosf(config->player.angle + angle_offset)
		* move_distance;
	new_y = config->player.y + sinf(config->player.angle + angle_offset)
		* move_distance;
	grid_x = (int)new_x;
	grid_y = (int)new_y;
	if (grid_x < 0 || grid_x >= map->width || grid_y < 0
		|| grid_y >= map->height)
		return (false);
	if (map->grid[grid_y][grid_x] == '1')
		return (false);
	frac_x = new_x - grid_x;
	frac_y = new_y - grid_y;
	if (frac_x < COLLISION_MARGIN && grid_x > 0
		&& map->grid[grid_y][grid_x - 1] == '1')
		return (false);
	if ((1.0f - frac_x) < COLLISION_MARGIN && grid_x < map->width - 1
		&& map->grid[grid_y][grid_x + 1] == '1')
		return (false);
	if (frac_y < COLLISION_MARGIN && grid_y > 0
		&& map->grid[grid_y - 1][grid_x] == '1')
		return (false);
	if ((1.0f - frac_y) < COLLISION_MARGIN && grid_y < map->height - 1
		&& map->grid[grid_y + 1][grid_x] == '1')
		return (false);
	return (true);
}

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
	ft_printf("[DEBUG] Initializing memory manager...\n");
	if (!mem_init(&mem))
	{
		ft_printf("[ERROR] Memory initialization failed. Exiting...\n");
		return (1);
	}
	config.memory = &mem;
	ft_printf("[DEBUG] Initializing configuration...\n");
	initialize_config(&config);
	ft_printf("[DEBUG] Validating arguments and parsing map...\n");
	if (!validate_args_and_load_map(argc, argv, &config, &mem))
	{
		ft_printf("[ERROR] Failed to validate and load map.\n");
		return (1);
	}
	ft_printf("[DEBUG] Validating map structure...\n");
	validate_map(&config.map);
	ft_printf("[DEBUG] Initializing MLX window...\n");
	config.map.mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT,
			"Cube3D - Textured Walls", true);
	if (!config.map.mlx)
	{
		ft_printf("[ERROR] Failed to initialize MLX.\n");
		ft_clean(&config.map, &mem, &config.resources);
		return (1);
	}
	if (config.use_textures)
	{
		ft_printf("[DEBUG] Loading textures...\n");
		load_textures(&config.resources, &config.textures, config.map.mlx,
			config.memory);
	}
	else
	{
		ft_printf("[DEBUG] Skipping texture loading, using colors instead.\n");
	}
	ft_printf("[DEBUG] Textures successfully loaded. Starting game loop...\n");
	game_loop(&config.map, &config);
	ft_printf("[DEBUG] Cleaning up resources...\n");
	cleanup_resources(&config.resources, config.map.mlx);
	ft_clean(&config.map, &mem, &config.resources);
	return (0);
}
