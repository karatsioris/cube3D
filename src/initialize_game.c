/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_game.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piotrwojnarowski <piotrwojnarowski@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:51:11 by piotrwojnar       #+#    #+#             */
/*   Updated: 2025/01/06 16:45:24 by piotrwojnar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	initialize_game(t_config *config, t_map *map)
{
	ft_printf("[DEBUG] Validating map boundaries...\n");
	validate_map_boundary(map);
	ft_printf("[DEBUG] Validating textures and colors...\n");
	validate_textures_and_colors(config);
	ft_printf("[DEBUG] Game initialized successfully.\n");
}

void	initialize_config(t_config *config)
{
	config->textures.north = NULL;
	config->textures.south = NULL;
	config->textures.west = NULL;
	config->textures.east = NULL;
	config->colors.floor[0] = -1;
	config->colors.floor[1] = -1;
	config->colors.floor[2] = -1;
	config->colors.ceiling[0] = -1;
	config->colors.ceiling[1] = -1;
	config->colors.ceiling[2] = -1;
	config->player.x = -1;
	config->player.y = -1;
	config->player.direction = '\0';
	config->map.grid = NULL;
	config->map.width = 0;
	config->map.height = 0;
	config->map.fd = -1;
	config->map.path = NULL;
	config->map.current_row = 0;
	config->map.player_n = 0;
	config->map.wall_n = 0;
	config->map.mlx = NULL;
	config->map.list = NULL;
	config->resources.textures = NULL;
	config->resources.texture_count = 0;
	config->resources.images = NULL;
	config->resources.image_count = 0;
	ft_printf("[DEBUG] Configuration initialized successfully.\n");
}
