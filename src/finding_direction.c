/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finding_direction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piotrwojnarowski <piotrwojnarowski@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 09:46:07 by piotrwojnar       #+#    #+#             */
/*   Updated: 2025/01/01 14:27:56 by piotrwojnar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

t_position	find_element(char **map, char element, int height, int width)
{
	t_position	pos;
	int			row;
	int			col;

	pos.row = -1;
	pos.col = -1;
	row = 0;
	while (row < height)
	{
		col = 0;
		while (col < width)
		{
			if (map[row][col] == element)
			{
				pos.row = row;
				pos.col = col;
				return (pos);
			}
			col++;
		}
		row++;
	}
	return (pos);
}

void	initialize_player(t_config *config, t_map *map)
{
	t_position	pos;

	pos = find_element(map->grid, 'N', map->height, map->width);
	if (pos.row == -1 && pos.col == -1)
		pos = find_element(map->grid, 'S', map->height, map->width);
	if (pos.row == -1 && pos.col == -1)
		pos = find_element(map->grid, 'E', map->height, map->width);
	if (pos.row == -1 && pos.col == -1)
		pos = find_element(map->grid, 'W', map->height, map->width);

	if (pos.row == -1 && pos.col == -1)
		ft_error(-7);
	config->player.x = pos.col;
	config->player.y = pos.row;
	config->player.direction = map->grid[pos.row][pos.col];
	map->grid[pos.row][pos.col] = '0';
}
