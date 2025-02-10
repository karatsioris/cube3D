/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_and_argv_valid.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 09:32:54 by piotrwojnar       #+#    #+#             */
/*   Updated: 2025/02/10 14:38:07 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	validate_args_and_load_map(int argc,
			char **argv, t_config *config, t_memory *mem)
{
	if (argc < 2)
	{
		ft_printf("[ERROR] Missing map path argument!\n");
		return (false);
	}
	else if (argc > 2)
	{
		ft_printf("[ERROR] Too many arguments! Received %d arguments.\n", argc);
		return (false);
	}
	parse_cub_file(config, mem, argv[1]);
	ft_printf("[DEBUG] Map parsed and loaded successfully.\n");
	return (true);
}

int	has_valid_extension(const char *path, const char *extension)
{
	int			path_len;
	int			ext_len;
	const char	*path_ext;

	path_len = ft_strlen(path);
	ext_len = ft_strlen(extension);
	if (path_len < ext_len)
		return (0);
	path_ext = path + path_len - ext_len;
	while (*extension)
	{
		if (*path_ext != *extension)
			return (0);
		path_ext++;
		extension++;
	}
	return (1);
}

bool	init_config_and_map(t_config *config, t_memory *mem,
	int argc, char **argv)
{
	ft_memset(config, 0, sizeof(*config));
	ft_memset(mem, 0, sizeof(*mem));
	config->use_textures = true;
	if (!mem_init(mem))
		return (false);
	config->memory = mem;
	initialize_config(config);
	if (!validate_args_and_load_map(argc, argv, config, mem))
		return (false);
	validate_map(&config->map);
	config->map.mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT,
			"Cube3D - Textured Walls", false);
	if (!config->map.mlx)
	{
		ft_clean(&config->map, mem, &config->resources);
		return (false);
	}
	load_textures(&config->resources, &config->textures, config->map.mlx,
		config->memory);
	return (true);
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
}

void	validate_config(t_config *config)
{
	if (config->colors.ceiling[0] == -1
		|| config->colors.ceiling[1] == -1
		|| config->colors.ceiling[2] == -1)
	{
		ft_printf("[ERROR] Missing ceiling color C in configuration.\n");
		exit(1);
	}
	if (config->colors.floor[0] == -1
		|| config->colors.floor[1] == -1
		|| config->colors.floor[2] == -1)
	{
		ft_printf("[ERROR] Missing floor color F in configuration.\n");
		exit(1);
	}
}
