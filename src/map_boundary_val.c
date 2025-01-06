/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_boundary_val.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piotrwojnarowski <piotrwojnarowski@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 09:40:11 by piotrwojnar       #+#    #+#             */
/*   Updated: 2025/01/06 12:54:36 by piotrwojnar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	validate_top_bottom_walls(char *line, int width, int is_top)
{
	int	i;

	ft_printf("[DEBUG] Validating %s wall: %s\n",
		is_top ? "Top" : "Bottom", line);
	if (!line)
	{
		ft_printf("[ERROR] Line is NULL while validating %s wall.\n",
			is_top ? "Top" : "Bottom");
		exit(1);
	}
	i = 0;
	while (i < width)
	{
		if (line[i] != '1')
		{
			ft_printf("[ERROR] %s wall is not closed at index %d (value: %c)\n",
				is_top ? "Top" : "Bottom", i, line[i]);
			exit(1);
		}
		i++;
	}
	ft_printf("[DEBUG] %s wall validated successfully.\n",
		is_top ? "Top" : "Bottom");
}

void	validate_side_walls(char *line, int width)
{
	ft_printf("[DEBUG] Validating side walls: %s\n", line);
	if (!line)
	{
		ft_printf("[ERROR] Line is NULL while validating side walls.\n");
		exit(1);
	}
	if (line[0] != '1' || line[width - 1] != '1')
	{
		ft_printf("[ERROR] Side walls are not fully closed: Start=%c, End=%c\n",
			line[0], line[width - 1]);
		exit(1);
	}
	ft_printf("[DEBUG] Side walls validated successfully.\n");
}

void	validate_map_boundary(t_map *map)
{
	int	i;

	ft_printf("[DEBUG] Validating map boundaries...\n");
	if (!map)
	{
		ft_printf("[ERROR] Map structure is NULL.\n");
		exit(1);
	}
	if (!map->grid)
	{
		ft_printf("[ERROR] Map grid is NULL.\n");
		exit(1);
	}
	ft_printf("[DEBUG] Map dimensions - Height: %d, Width: %d\n",
		map->height, map->width);
	if (map->height < 2 || map->width < 2)
	{
		ft_printf("[ERROR] Invalid map dimensions. Height=%d, Width=%d\n",
			map->height, map->width);
		exit(1);
	}
	ft_printf("[DEBUG] Validating top wall...\n");
	validate_top_bottom_walls(map->grid[0], map->width, 1);
	ft_printf("[DEBUG] Validating bottom wall...\n");
	validate_top_bottom_walls(map->grid[map->height - 1], map->width, 0);
	i = 1;
	while (i < map->height - 1)
	{
		ft_printf("[DEBUG] Validating side walls of row %d...\n", i);
		if (!map->grid[i])
		{
			ft_printf("[ERROR] Row %d is NULL.\n", i);
			exit(1);
		}
		validate_side_walls(map->grid[i], map->width);
		i++;
	}
	ft_printf("[DEBUG] Map boundaries validated successfully.\n");
}
