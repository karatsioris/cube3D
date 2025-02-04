/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_game.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:51:11 by piotrwojnar       #+#    #+#             */
/*   Updated: 2025/02/04 14:39:07 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

// void	initialize_config(t_config *config)
// {
// 	config->textures.north = NULL;
// 	config->textures.south = NULL;
// 	config->textures.west = NULL;
// 	config->textures.east = NULL;
// 	config->colors.floor[0] = -1;
// 	config->colors.floor[1] = -1;
// 	config->colors.floor[2] = -1;
// 	config->colors.ceiling[0] = -1;
// 	config->colors.ceiling[1] = -1;
// 	config->colors.ceiling[2] = -1;
// 	config->colors.wall[0] = -1;
// 	config->colors.wall[1] = -1;
// 	config->colors.wall[2] = -1;
// 	config->player.x = -1;
// 	config->player.y = -1;
// 	config->player.angle = 3.14;
// 	config->player.direction = '\0';
// 	config->map.grid = NULL;
// 	config->map.width = 0;
// 	config->map.height = 0;
// 	config->map.fd = -1;
// 	config->map.path = NULL;
// 	config->map.current_row = 0;
// 	config->map.player_n = 0;
// 	config->map.wall_n = 0;
// 	config->map.mlx = NULL;
// 	config->map.list = NULL;
// 	config->resources.textures = NULL;
// 	config->resources.texture_count = 0;
// 	config->resources.images = NULL;
// 	config->resources.image_count = 0;
// 	ft_printf("[DEBUG] Configuration initialized successfully.\n");
// }
void	initialize_map(t_map *map)
{
	map->grid = NULL;
	map->width = 0;
	map->height = 0;
	map->fd = -1;
	map->path = NULL;
	map->current_row = 0;
	map->player_n = 0;
	map->wall_n = 0;
	map->mlx = NULL;
	map->list = NULL;
}

void	initialize_resources(t_resources *resources, t_texture *textures,
	t_color *colors, t_player *player)
{
	textures->north = NULL;
	textures->south = NULL;
	textures->west = NULL;
	textures->east = NULL;
	colors->floor[0] = -1;
	colors->floor[1] = -1;
	colors->floor[2] = -1;
	colors->ceiling[0] = -1;
	colors->ceiling[1] = -1;
	colors->ceiling[2] = -1;
	colors->wall[0] = -1;
	colors->wall[1] = -1;
	colors->wall[2] = -1;
	player->x = -1;
	player->y = -1;
	player->angle = 3.14;
	player->direction = '\0';
	resources->textures = NULL;
	resources->texture_count = 0;
	resources->images = NULL;
	resources->image_count = 0;
}

void	initialize_config(t_config *config)
{
	initialize_map(&config->map);
	initialize_resources(&config->resources, &config->textures, &config->colors,
		&config->player);
	ft_printf("[DEBUG] Configuration initialized successfully.\n");
}
