/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaratsi <kkaratsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 12:23:56 by piotrwojnar       #+#    #+#             */
/*   Updated: 2025/01/30 16:41:03 by kkaratsi         ###   ########.fr       */
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

// void	player_move_handler(mlx_key_data_t keydata, t_config *config)
// {
// 	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
// 	{
// 		if (keydata.key == MLX_KEY_W)
// 			config->player.y -= 0.1;
// 		else if (keydata.key == MLX_KEY_S)
// 			config->player.y += 0.1;
// 		else if (keydata.key == MLX_KEY_A)
// 			config->player.x -= 0.1;
// 		else if (keydata.key == MLX_KEY_D)
// 			config->player.x += 0.1;
// 		else if (keydata.key == MLX_KEY_LEFT)
// 			config->player.angle -= 0.1;
// 		else if (keydata.key == MLX_KEY_RIGHT)
// 			config->player.angle += 0.1;
// 	}
// 	render_scene(config->map.mlx, &config->map, config, WINDOW_HEIGHT);
// }

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

// this function is not used for images that are not mlx_image_t
// void	clear_image(t_config *config, uint32_t color)
// {
// 	int x;
// 	int y;
	
// 	if (config == NULL || config->resources.images == NULL || config->resources.images[0] == NULL)
//     {
//         fprintf(stderr, "Error: Invalid config or image resource\n");
//         return;
//     }
// 	x = 0;
// 	while (x < WINDOW_WIDTH)
// 	{
// 		y = 0;
// 		while (y < WINDOW_HEIGHT)
// 		{
// 			mlx_put_pixel(config->resources.images[0], x, y, color);
// 			y++;
// 		}
// 		x++;
// 	}
// 	mlx_image_to_window(config->map.mlx, config->resources.images[0], 0, 0);
// }

// this function is not used for mlx_image_t *img
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


void	load_textures(t_resources *res, t_texture *textures,
	mlx_t *mlx, t_memory *mem, t_map *map)
{
	bool	use_textures = false;
	  if (!use_textures)
    {
        ft_printf("[DEBUG] Skipping texture loading, using colors instead.\n");
        return;
    }
	
	xpm_t	*xpm_texture;

	ft_printf("[DEBUG] Allocating memory for textures and images...\n");
	res->images = mem_alloc(mem, sizeof(mlx_image_t *) * 4);
	if (!res->images)
	{
		ft_printf("[ERROR] Failed to allocate memory for images.\n");
		cleanup_textures(res, mlx);
		exit(1);
	}
	if (!map->grid)
	{
		ft_printf("[ERROR] Map grid is not initialized.\n");
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
		if (!texture_paths[i])
		{
			ft_printf("[ERROR] Texture path %d is NULL.\n", i);
			cleanup_textures(res, mlx);
			exit(1);
		}
		ft_printf("[DEBUG] Loading texture: %s\n", texture_paths[i]); 
		xpm_texture = mlx_load_xpm42(texture_paths[i]);
		if (!xpm_texture)
		{
			ft_printf("[ERROR] Failed to load XPM texture: %s\n",
				texture_paths[i]);
			cleanup_textures(res, mlx);
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
			cleanup_textures(res, mlx);
			exit(1);
		}
		ft_printf("[DEBUG] Freeing intermediate XPM texture: %s\n",
			texture_paths[i]);
		mlx_delete_xpm42(xpm_texture);
		ft_printf("[DEBUG] Texture %d loaded successfully.\n", i);
	}
	ft_printf("[DEBUG] All textures loaded successfully.\n");
}

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

void	validate_file_extension(t_map *map)
{
	if (!has_valid_extension(map->path, ".cub"))
	{
		ft_printf("[ERROR] Invalid file extension. Expected '.cub'\n");
		exit(1);
	}
	ft_printf("[DEBUG] File extension validated successfully.\n");
}

void	get_map_dimensions(t_map *map)
{
	if (!map || !map->grid)
	{
		printf("[ERROR] Invalid map structure or grid.\n");
		exit(1);
	}
	map->height = 0;
	while (map->grid[map->height])
		map->height++;
	if (map->grid[0])
		map->width = ft_strlen(map->grid[0]);
	else
		map->width = 0;
	printf("[DEBUG] Map dimensions calculated: Height=%d, Width=%d\n",
		map->height, map->width);
}

void	validate_map(t_map *map, t_memory *mem)
{
	ft_printf("[DEBUG] ----- Validating Map Structure -----\n");
	ft_printf("[DEBUG] Printing linked list before converting to grid...\n");

	ft_printf("[DEBUG] Validating file extension...\n");
	validate_file_extension(map);
	ft_printf("[DEBUG] File extension validated.\n");
	ft_printf("[DEBUG] Converting map list to grid array...\n");
	list_to_array(map, mem);
	ft_printf("[DEBUG] Map list converted to grid array.\n");
	ft_printf("[DEBUG] Calculating map dimensions...\n");
	get_map_dimensions(map);
	ft_printf("[DEBUG] Map dimensions calculated: Height=%d, Width=%d\n",
		map->height, map->width);
	ft_printf("[DEBUG] Printing map grid...\n");
	for (int i = 0; map->grid[i]; i++)
		ft_printf("[DEBUG] Grid Row %d: '%s'\n", i, map->grid[i]);
	ft_printf("[DEBUG] Validating map boundaries...\n");
	validate_map_boundary(map);
	ft_printf("[DEBUG] Map boundaries validated.\n");
	ft_printf("[DEBUG] ----- Map Structure Validated Successfully -----\n");
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
	validate_map(&config.map, &mem);
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
	
	load_textures(&config.resources, &config.textures, config.map.mlx,
		&mem, &config.map);
	ft_printf("[DEBUG] Textures successfully loaded. Starting game loop...\n");
	game_loop(&config.map, &config);
	ft_printf("[DEBUG] Cleaning up resources...\n");
	cleanup_resources(&config.resources, config.map.mlx);
	ft_clean(&config.map, &mem, &config.resources);
	return (0);
}
