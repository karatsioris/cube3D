/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_game.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaratsi <kkaratsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:51:11 by piotrwojnar       #+#    #+#             */
/*   Updated: 2025/01/23 15:51:45 by kkaratsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

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
	config->colors.wall[0] = -1;
	config->colors.wall[1] = -1;
	config->colors.wall[2] = -1;
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
