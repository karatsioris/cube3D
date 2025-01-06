/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piotrwojnarowski <piotrwojnarowski@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 12:23:56 by piotrwojnar       #+#    #+#             */
/*   Updated: 2025/01/06 11:35:14 by piotrwojnar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	initialize_game(t_config *config, t_map *map)
{
	ft_printf("[DEBUG] Validating map boundaries...\n");
	validate_map_boundary(map);

	ft_printf("[DEBUG] Initializing player position...\n");
	initialize_player(config, map);

	ft_printf("[DEBUG] Validating textures and colors...\n");
	validate_textures_and_colors(config);

	ft_printf("[DEBUG] Game initialized successfully.\n");
}

void key_event_handler(mlx_key_data_t keydata, void *param)
{
	(void)param;

	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		ft_printf("[DEBUG] ESC key pressed. Closing window...\n");
		exit(0);
	}
}

void	load_textures(t_resources *res, t_texture *textures,
	mlx_t *mlx, t_memory *mem)
{
	xpm_t	*xpm_texture;

	ft_printf("[DEBUG] Allocating memory for textures and images...\n");
	res->images = mem_alloc(mem, sizeof(mlx_image_t *) * 4);
	if (!res->images)
	{
		ft_printf("[ERROR] Failed to allocate memory for images.\n");
		exit(1);
	}
	const char *texture_paths[] = {
		textures->north,
		textures->south,
		textures->west,
		textures->east
	};

	for (int i = 0; i < 4; i++)
	{
		ft_printf("[DEBUG] Loading texture: %s\n", texture_paths[i]);
		xpm_texture = mlx_load_xpm42(texture_paths[i]);
		if (!xpm_texture)
		{
			ft_printf("[ERROR] Failed to load XPM texture: %s\n",
				texture_paths[i]);
			exit(1);
		}
		ft_printf("[DEBUG] Creating image from texture: %s\n",
			texture_paths[i]);
		res->images[i] = mlx_texture_to_image(mlx, &xpm_texture->texture);
		if (!res->images[i])
		{
			ft_printf("[ERROR] Failed to create image from XPM texture: %s\n",
				texture_paths[i]);
			mlx_delete_xpm42(xpm_texture);
			exit(1);
		}
		ft_printf("[DEBUG] Freeing intermediate XPM texture: %s\n",
			texture_paths[i]);
		mlx_delete_xpm42(xpm_texture);
		ft_printf("[DEBUG] Texture %d loaded successfully.\n", i);
		mem_alloc(mem, sizeof(mlx_image_t));
	}
	ft_printf("[DEBUG] All textures loaded successfully.\n");
}

void	game_loop(mlx_t *mlx)
{
	ft_printf("[DEBUG] Starting game loop...\n");
	mlx_key_hook(mlx, key_event_handler, NULL);
	mlx_loop(mlx);
	ft_printf("[DEBUG] Game loop ended.\n");
}

int	main(int argc, char **argv)
{
	t_config	config = {0};
	t_memory	mem = {0};

	ft_printf("[DEBUG] Initializing memory manager...\n");
	if (!mem_init(&mem))
	{
		ft_printf("[ERROR] Memory initialization failed. Exiting...\n");
		return (1);
	}
	ft_printf("[DEBUG] Validating arguments and parsing map...\n");
	validate_args_and_load_map(argc, argv, &config, &mem);
	ft_printf("[DEBUG] Initializing MLX window...\n");
	config.map.mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Cube3D", true);
	if (!config.map.mlx)
	{
		ft_printf("[ERROR] Failed to initialize MLX.\n");
		ft_clean(&config.map, &mem);
		return (1);
	}
	ft_printf("[DEBUG] Initializing game configuration...\n");
	initialize_game(&config, &config.map);
	ft_printf("[DEBUG] Loading textures...\n");
	load_textures(&config.resources, &config.textures, config.map.mlx, &mem);
	ft_printf("[DEBUG] Starting game loop...\n");
	game_loop(config.map.mlx);
	ft_printf("[DEBUG] Cleaning up resources...\n");
	cleanup_resources(&config.resources, config.map.mlx);
	ft_clean(&config.map, &mem);
	return (0);
}
