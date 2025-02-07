/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_game.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:51:11 by piotrwojnar       #+#    #+#             */
/*   Updated: 2025/02/05 17:40:07 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

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
