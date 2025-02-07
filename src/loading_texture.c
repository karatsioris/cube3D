/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaratsi <kkaratsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:24:38 by pwojnaro          #+#    #+#             */
/*   Updated: 2025/02/06 14:12:35 by kkaratsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	load_textures(t_resources *res, t_texture *textures, mlx_t *mlx,
	t_memory *mem)
{
	mlx_texture_t	*tex;
	int				count;
	int				i;
	char			*paths[4];

	paths[0] = textures->north;
	paths[1] = textures->south;
	paths[2] = textures->east;
	paths[3] = textures->west;
	count = 4;
	res->texture_count = count;
	res->images = mem_alloc(mem, sizeof(mlx_image_t *) * count);
	if (!res->images)
	{
		ft_printf("[ERROR] Failed to allocate memory for images.\n");
		cleanup_textures(res, mlx);
		exit(1);
	}
	i = 0;
	while (i < count)
	{
		if (!paths[i])
		{
			cleanup_textures(res, mlx);
			exit(1);
		}
		if (access(paths[i], F_OK) == -1)
		{
			perror("[ERROR] File does not exist or cannot be accessed");
			cleanup_textures(res, mlx);
			exit(1);
		}
		tex = mlx_load_png(paths[i]);
		if (!tex)
		{
			cleanup_textures(res, mlx);
			exit(1);
		}
		res->images[i] = mlx_texture_to_image(mlx, tex);
		if (!res->images[i])
		{
			mlx_delete_texture(tex);
			cleanup_textures(res, mlx);
			exit(1);
		}
		mlx_delete_texture(tex);
		i++;
	}
	res->image_count = count;
}

void	render_scene_wrapper(void *param)
{
	t_render_data	*data;

	data = (t_render_data *)param;
	render_scene(data, WINDOW_HEIGHT);
}

void	key_event_handler(mlx_key_data_t keydata, void *param)
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

void	game_loop(t_map *map, t_config *config)
{
	t_render_data	*data;

	config->img = mlx_new_image(map->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	data = mem_alloc(config->memory, sizeof(t_render_data));
	if (!data)
	{
		ft_printf("[ERROR] Failed to allocate memory for render data.\n");
		exit(1);
	}
	data->mlx = map->mlx;
	data->map = map;
	data->config = config;
	data->img = config->img;
	mlx_key_hook(map->mlx, key_event_handler, config);
	mlx_loop_hook(map->mlx, render_scene_wrapper, data);
	mlx_loop(map->mlx);
	ft_printf("[DEBUG] Game loop ended.\n");
}
