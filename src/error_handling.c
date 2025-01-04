/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piotrwojnarowski <piotrwojnarowski@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 09:51:55 by piotrwojnar       #+#    #+#             */
/*   Updated: 2025/01/04 13:08:55 by piotrwojnar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	ft_error(int code)
{
	if (code == -1)
	{
		ft_printf("Error: The map is not rectangular!\n");
	}
	else if (code == -2)
	{
		ft_printf("Error: Memory allocation failed!\n");
	}
	else if (code == -3)
	{
		ft_printf("Error: More than one player 'P' found in the map!\n");
	}
	else if (code == -4)
	{
		ft_printf("Error: More than one exit 'E' found in the map!\n");
	}
	else if (code == -5)
	{
		ft_printf(" Unknown Symbol found in the map!\n");
	}
	else if (code == -6)
	{
		ft_printf("Error: Initialization failed!\n");
	}
	exit(1);
}

void	get_map_dimensions(t_map *map)
{
	int	i;
	int	row_length;

	ft_printf("[DEBUG] ----- Calculating Map Dimensions -----\n");
	if (!map || !map->grid)
	{
		ft_printf("[ERROR] Map or Map grid is NULL!\n");
		exit(1);
	}
	map->height = 0;
	map->width = 0;
	for (i = 0; map->grid[i]; i++)
	{
		row_length = ft_strlen(map->grid[i]);
		ft_printf("[DEBUG] Row %d Length: %d | Content: '%s'\n",
			i, row_length, map->grid[i]);

		if (row_length > map->width)
			map->width = row_length;

		map->height++;
	}
	ft_printf("Map Dimensions: Height=%d, Width=%d\n", map->height, map->width);

	if (map->height == 0 || map->width == 0)
	{
		ft_printf("[ERROR] Invalid map dimensions detected.\n");
		exit(1);
	}
	ft_printf("[DEBUG] ----- Map Dimensions Calculated Successfully -----\n");
}

void	validate_map(t_map *map, t_memory *mem)
{
	ft_printf("[DEBUG] ----- Validating Map Structure -----\n");
	validate_file_extension(map);
	ft_printf("[DEBUG] File extension validated.\n");
	ft_printf("[DEBUG] Converting map list to grid array...\n");
	list_to_array(map, mem);
	ft_printf("[DEBUG] Map list converted to grid array.\n");
	ft_printf("[DEBUG] Printing map grid...\n");
	for (int i = 0; map->grid[i]; i++)
		ft_printf("[DEBUG] Grid Row %d: '%s'\n", i, map->grid[i]);
	ft_printf("[DEBUG] Calculating map dimensions...\n");
	get_map_dimensions(map);
	ft_printf("[DEBUG] Map dimensions calculated: Height=%d, Width=%d\n",
		map->height, map->width);
	ft_printf("[DEBUG] Validating map boundaries...\n");
	validate_map_boundary(map);
	ft_printf("[DEBUG] Map boundaries validated.\n");

	ft_printf("[DEBUG] ----- Map Structure Validated Successfully -----\n");
}
