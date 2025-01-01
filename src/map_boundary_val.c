/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_boundary_val.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piotrwojnarowski <piotrwojnarowski@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 09:40:11 by piotrwojnar       #+#    #+#             */
/*   Updated: 2025/01/01 15:38:03 by piotrwojnar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	validate_top_bottom_walls(char *line, int width, int is_top)
{
	int	i;

	i = 0;
	while (i < width)
	{
		if (line[i] != '1')
		{
			if (is_top)
				printf("Error: Top wall is not fully closed at index %d\n", i);
			else
				printf("Error: Bottom wall is not fully closed at %d\n", i);
			exit(1);
		}
		i++;
	}
}

void	validate_side_walls(char *line, int width)
{
	if (line[0] != '1' || line[width - 1] != '1')
	{
		printf("Error: Side walls are not fully closed.\n");
		exit(1);
	}
}

void	validate_map_boundary(t_map *map)
{
	int	i;

	i = 0;
	validate_top_bottom_walls(map->grid[0], map->width, 1);
	validate_top_bottom_walls(map->grid[map->height - 1], map->width, 0);

	while (i < map->height - 1)
	{
		validate_side_walls(map->grid[i], map->width);
		i++;
	}
}
