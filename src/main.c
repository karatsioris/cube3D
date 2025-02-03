/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaratsi <kkaratsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 12:23:56 by piotrwojnar       #+#    #+#             */
/*   Updated: 2025/02/03 09:59:15 by kkaratsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	key_event_handler(mlx_key_data_t keydata, void *param)
{
	(void)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		ft_printf("[DEBUG] ESC key pressed. Closing window...\n");
		exit(0);
	}
	else
		player_move_handler(keydata, param);
}

void player_move_handler(mlx_key_data_t keydata, void *param)
{
	t_config *config = (t_config *)param;
	float move_speed = 0.3f;
	float rot_speed = 0.3f; 

	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		switch (keydata.key)
		{
			case MLX_KEY_W:
				config->player.x += cosf(config->player.angle) * move_speed;
				config->player.y += sinf(config->player.angle) * move_speed;
				break;
			case MLX_KEY_S:
				config->player.x -= cosf(config->player.angle) * move_speed;
				config->player.y -= sinf(config->player.angle) * move_speed;
				break;
			case MLX_KEY_A:
				config->player.x += cosf(config->player.angle - M_PI_2) * move_speed;
				config->player.y += sinf(config->player.angle - M_PI_2) * move_speed;
				break;
			case MLX_KEY_D:
				config->player.x += cosf(config->player.angle + M_PI_2) * move_speed;
				config->player.y += sinf(config->player.angle + M_PI_2) * move_speed;
				break;
			case MLX_KEY_LEFT:
				config->player.angle -= rot_speed;
				break;
			case MLX_KEY_RIGHT:
				config->player.angle += rot_speed;
				break;
			default:
				break;
		}
		// render_scene(config->map.mlx, &config->map, config, WINDOW_HEIGHT);
	}
}

void clear_image(mlx_image_t *img, uint32_t color)
{
	for (uint32_t y = 0; y < img->height; y++)
	{
		for (uint32_t x = 0; x < img->width; x++)
		{
			mlx_put_pixel(img, x, y, color);
		}
	}
}

void load_textures(t_resources *res, t_texture *textures, mlx_t *mlx, t_memory *mem)
{
	int count = 4;
	res->texture_count = count;
	
	res->images = mem_alloc(mem, sizeof(mlx_image_t *) * count);
	if (!res->images)
	{
		ft_printf("[ERROR] Failed to allocate memory for images.\n");
		cleanup_textures(res, mlx);
		exit(1);
	}
	
	char *paths[4];
	paths[0] = textures->north;
	paths[1] = textures->south;
	paths[2] = textures->west;
	paths[3] = textures->east;
	
	for (int i = 0; i < count; i++)
	{
		if (!paths[i])
		{
			ft_printf("[ERROR] Texture path %d is NULL.\n", i);
			cleanup_textures(res, mlx);
			exit(1);
		}
		
		ft_printf("[DEBUG] Verifying existence of file: %s\n", paths[i]);
		if (access(paths[i], F_OK) == -1)
		{
			perror("[ERROR] File does not exist or cannot be accessed");
			ft_printf("[DEBUG] Failed texture path: %s\n", paths[i]);
			cleanup_textures(res, mlx);
			exit(1);
		}
		mlx_texture_t *tex = mlx_load_png(paths[i]);
		if (!tex)
		{
			ft_printf("[ERROR] Failed to load PNG texture: %s\n", paths[i]);
			cleanup_textures(res, mlx);
			exit(1);
		}
		
		ft_printf("[DEBUG] Loaded texture dimensions: %dx%d\n", tex->width, tex->height);
		ft_printf("[DEBUG] Converting texture to image...\n");
		res->images[i] = mlx_texture_to_image(mlx, tex);
		if (!res->images[i])
		{
			ft_printf("[ERROR] Failed to create image from PNG texture: %s\n", paths[i]);
			mlx_delete_texture(tex);
			cleanup_textures(res, mlx);
			exit(1);
		}
		
		ft_printf("[DEBUG] Freeing intermediate PNG texture...\n");
		mlx_delete_texture(tex);
		ft_printf("[DEBUG] Texture %d loaded successfully from: %s\n", i, paths[i]);
	}
	
	res->image_count = count;
}

void render_scene_wrapper(void *param)
{
    t_config *config = (t_config *)param;
    render_scene(config->map.mlx, &config->map, config, WINDOW_HEIGHT, config->img);
}

void	game_loop(t_map *map, t_config *config)
{	
	config->img = mlx_new_image(map->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	
	mlx_key_hook(map->mlx, key_event_handler, config);
    mlx_loop_hook(map->mlx, render_scene_wrapper, config);
	mlx_loop(map->mlx);
	ft_printf("[DEBUG] Game loop ended.\n");
}

int main(int argc, char **argv)
{
	t_config config = {0};
	t_memory mem = {0};

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
	config.map.mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Cube3D - Textured Walls", true);
	if (!config.map.mlx)
	{
		ft_printf("[ERROR] Failed to initialize MLX.\n");
		ft_clean(&config.map, &mem, &config.resources);
		return (1);
	}
	if (config.use_textures)
	{
		ft_printf("[DEBUG] Loading textures...\n");
		load_textures(&config.resources, &config.textures, config.map.mlx, config.memory);
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
