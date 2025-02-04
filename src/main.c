/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 12:23:56 by piotrwojnar       #+#    #+#             */
/*   Updated: 2025/02/04 14:15:35 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#define COLLISION_MARGIN 0.1f

bool can_move_forward(t_config *config, t_map *map, float move_distance, float angle_offset)
{
	float new_x = config->player.x + cosf(config->player.angle + angle_offset) * move_distance;
	float new_y = config->player.y + sinf(config->player.angle + angle_offset) * move_distance;
	
	int grid_x = (int)new_x;
	int grid_y = (int)new_y;

	// Check boundaries first
	if (grid_x < 0 || grid_x >= map->width || grid_y < 0 || grid_y >= map->height)
		return false;
	
	// If the grid cell is a wall, no movement is allowed
	if (map->grid[grid_y][grid_x] == '1')
		return false;
	
	float frac_x = new_x - grid_x;
	float frac_y = new_y - grid_y;
	
	// Check left edge of cell
	if (frac_x < COLLISION_MARGIN && grid_x > 0 && map->grid[grid_y][grid_x - 1] == '1')
		return false;
	
	// Check right edge of cell
	if ((1.0f - frac_x) < COLLISION_MARGIN && grid_x < map->width - 1 && map->grid[grid_y][grid_x + 1] == '1')
		return false;
	
	// Check top edge of cell
	if (frac_y < COLLISION_MARGIN && grid_y > 0 && map->grid[grid_y - 1][grid_x] == '1')
		return false;
	
	// Check bottom edge of cell
	if ((1.0f - frac_y) < COLLISION_MARGIN && grid_y < map->height - 1 && map->grid[grid_y + 1][grid_x] == '1')
		return false;

	return true;
}


/*
 * Updates the player's position by the given move distance and angle offset,
 * but only if the collision check passes. Otherwise, the player's position remains unchanged.
 */
void update_player_position(t_config *config, t_map *map, float move_distance, float angle_offset)
{
	if (can_move_forward(config, map, move_distance, angle_offset))
	{
		config->player.x += cosf(config->player.angle + angle_offset) * move_distance;
		config->player.y += sinf(config->player.angle + angle_offset) * move_distance;
	}
	else
	{
		ft_printf("[DEBUG] Movement blocked: Collision detected.\n");
	}
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
				update_player_position(config, &config->map, move_speed, 0.0f);
				break;
			case MLX_KEY_S:
				update_player_position(config, &config->map, move_speed, M_PI);
				break;
			case MLX_KEY_A:
				update_player_position(config, &config->map, move_speed, -M_PI_2);
				break;
			case MLX_KEY_D:
				update_player_position(config, &config->map, move_speed, M_PI_2);
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
		// Optionally, trigger a re-render here if your rendering is not continuously updating.
	}
}

/*
 * Key event handler which first checks for the ESC key to exit,
 * otherwise it passes the event to the player movement handler.
 */
void key_event_handler(mlx_key_data_t keydata, void *param)
{
	(void)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		ft_printf("[DEBUG] ESC key pressed. Closing window...\n");
		exit(0);
	}
	else
	{
		player_move_handler(keydata, param);
	}
}

/*
 * Clears the entire image to a specified color.
 */
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

/*
 * Loads textures from file paths. (This function is unchanged from your version.)
 */
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

/*
 * A wrapper that calls render_scene (presumed to be defined elsewhere)
 * to update the graphics on the window.
 */
void render_scene_wrapper(void *param)
{
	t_config *config = (t_config *)param;
	render_scene(config->map.mlx, &config->map, config, WINDOW_HEIGHT, config->img);
}

/*
 * The main game loop: creates an image, registers the key event and loop hooks,
 * and then starts the MLX loop.
 */
void game_loop(t_map *map, t_config *config)
{   
	config->img = mlx_new_image(map->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	
	mlx_key_hook(map->mlx, key_event_handler, config);
	mlx_loop_hook(map->mlx, render_scene_wrapper, config);
	mlx_loop(map->mlx);
	ft_printf("[DEBUG] Game loop ended.\n");
}

/*
 * Main function: Initializes configuration, validates the map, loads textures,
 * creates the MLX window, and starts the game loop.
 */
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