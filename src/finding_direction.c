/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finding_direction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piotrwojnarowski <piotrwojnarowski@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 09:46:07 by piotrwojnar       #+#    #+#             */
/*   Updated: 2025/01/04 13:06:38 by piotrwojnar      ###   ########.fr       */
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

	ft_printf("[DEBUG] Finding player start position...\n");
	pos = find_element(map->grid, 'N',
			map->height, map->width);
	if (pos.row == -1 && pos.col == -1)
	{
		ft_printf("[ERROR] Player start position not found!\n");
		exit(1);
	}
	ft_printf("[DEBUG] Player found at (%d, %d)\n", pos.row, pos.col);
	config->player.x = pos.col;
	config->player.y = pos.row;
	config->player.direction = map->grid[pos.row][pos.col];
	map->grid[pos.row][pos.col] = '0';
}
