/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 12:23:56 by piotrwojnar       #+#    #+#             */
/*   Updated: 2025/02/01 12:29:40 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

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

	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		switch (keydata.key)
		{
			case MLX_KEY_W:
				config->player.y -= 0.1;
				break;
			case MLX_KEY_S:
				config->player.y += 0.1;
				break;
			case MLX_KEY_A:
				config->player.x -= 0.1;
				break;
			case MLX_KEY_D:
				config->player.x += 0.1;
				break;
			case MLX_KEY_LEFT:
				config->player.angle -= 0.1;
				break;
			case MLX_KEY_RIGHT:
				config->player.angle += 0.1;
				break;
			default:
				break;
		}
		render_scene(config->map.mlx, &config->map, config, WINDOW_HEIGHT);
		printf("\nPlayer position: x = %d, y = %d angle = %f\n", config->player.x, config->player.y, config->player.angle);
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


// void	load_textures(t_resources *res, t_texture *textures,
// 	mlx_t *mlx, t_memory *mem, t_map *map)
// {
// 	bool	use_textures = false;
// 	  if (!use_textures)
//     {
//         ft_printf("[DEBUG] Skipping texture loading, using colors instead.\n");
//         return;
//     }
	
// 	xpm_t	*xpm_texture;

// 	ft_printf("[DEBUG] Allocating memory for textures and images...\n");
// 	res->images = mem_alloc(mem, sizeof(mlx_image_t *) * 4);
// 	if (!res->images)
// 	{
// 		ft_printf("[ERROR] Failed to allocate memory for images.\n");
// 		cleanup_textures(res, mlx);
// 		exit(1);
// 	}
// 	for (int i = 0; i < 4; i++)
// 	{
// 		ft_printf("[DEBUG] Checking texture path %d: %s\n", i,
// 			texture_paths[i]);
// 		if (!texture_paths[i])
// 		{
// 			ft_printf("[ERROR] Texture path %d is NULL.\n", i);
// 			cleanup_textures(res, mlx);
// 			exit(1);
// 		}
// 		ft_printf("[DEBUG] Verifying existence of file: %s\n",
// 			texture_paths[i]);
// 		if (access(texture_paths[i], F_OK) == -1)
// 		{
// 			perror("[ERROR] File does not exist or cannot be accessed");
// 			ft_printf("[DEBUG] Failed texture path: %s\n", texture_paths[i]);
// 			cleanup_textures(res, mlx);
// 			exit(1);
// 		}
// 		ft_printf("[DEBUG] Attempting to load texture: %s\n", texture_paths[i]);
// 		ft_printf("[DEBUG] Loading texture: %s\n", texture_paths[i]); 
// 		xpm_texture = mlx_load_xpm42(texture_paths[i]);
// 		if (!xpm_texture)
// 		{
// 			ft_printf("[ERROR] Failed to load XPM texture: %s\n",
// 				texture_paths[i]);
// 			cleanup_textures(res, mlx);
// 			exit(1);
// 		}
// 		ft_printf("[DEBUG] Loaded texture dimensions: %dx%d\n",
// 			xpm_texture->texture.width, xpm_texture->texture.height);
// 		if (xpm_texture->texture.width != 64
// 			|| xpm_texture->texture.height != 64)
// 		{
// 			ft_printf("[ERROR] Invalid for %s. Exp 64x64, found %dx%d.\n",
// 				texture_paths[i], xpm_texture->texture.width,
// 				xpm_texture->texture.height);
// 			mlx_delete_xpm42(xpm_texture);
// 			cleanup_textures(res, mlx);
// 			exit(1);
// 		}
// 		ft_printf("[DEBUG] Converting texture to image: %s\n",
// 			texture_paths[i]);
// 		res->images[i] = mlx_texture_to_image(mlx, &xpm_texture->texture);
// 		if (!res->images[i])
// 		{
// 			ft_printf("[ERROR] Failed to create image from XPM texture: %s\n",
// 				texture_paths[i]);
// 			mlx_delete_xpm42(xpm_texture);
// 			cleanup_textures(res, mlx);
// 			exit(1);
// 		}
// 		ft_printf("[DEBUG] Freeing intermediate XPM texture: %s\n",
// 			texture_paths[i]);
// 		mlx_delete_xpm42(xpm_texture);
// 		ft_printf("[DEBUG] Texture %d loaded successfully: %s\n", i,
// 			texture_paths[i]);
// 	}
// 	ft_printf("[DEBUG] All textures loaded successfully.\n");
// }

void	game_loop(t_map *map, t_config *config)
{	
	// ft_printf("k Starting game loop...\n");
	// ft_printf("k Player position: (%d, %d)\n", config->player.x, config->player.y);
	// ft_printf("k Use textures: %s\n", config->use_textures ? "true" : "false");
	// ft_printf("k Image pointer: %p\n", config->resources.images[0]);
	// mlx_key_hook(map->mlx, key_event_handler, NULL);
	mlx_key_hook(map->mlx, key_event_handler, config);
	render_scene(map->mlx, &config->map, config, WINDOW_HEIGHT);
	mlx_loop(map->mlx);
	ft_printf("[DEBUG] Game loop ended.\n");
}

int	main(int argc, char **argv)
{
	t_config	config = {0};
	t_memory	mem = {0};
	config.use_textures = false;

	ft_printf("[DEBUG] Initializing memory manager...\n");
	if (!mem_init(&mem))
	{
		ft_printf("[ERROR] Memory initialization failed. Exiting...\n");
		return (1);
	}
	ft_printf("[DEBUG] Initializing configuration...\n");
	initialize_config(&config);
	ft_printf("[DEBUG] Validating arguments and parsing map...\n");
	validate_args_and_load_map(argc, argv, &config, &mem);
	ft_printf("[DEBUG] Validating map structure...\n");
	validate_map(&config.map);
	ft_printf("[DEBUG] Initializing MLX window...\n");
	config.map.mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT,
			"Cube3D - Textures Loaded", true);
	if (!config.map.mlx)
	{
		ft_printf("[ERROR] Failed to initialize MLX.\n");
		ft_clean(&config.map, &mem, &config.resources);
		return (1);
	}
	ft_printf("[DEBUG] Loading textures...\n");
	
	// load_textures(&config.resources, &config.textures, config.map.mlx,
	// 	&mem);
	ft_printf("[DEBUG] Textures successfully loaded. Starting game loop...\n");
	game_loop(&config.map, &config);
	ft_printf("[DEBUG] Cleaning up resources...\n");
	cleanup_resources(&config.resources, config.map.mlx);
	ft_clean(&config.map, &mem, &config.resources);
	return (0);
}
