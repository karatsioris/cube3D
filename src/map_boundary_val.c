/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_boundary_val.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 09:40:11 by piotrwojnar       #+#    #+#             */
/*   Updated: 2025/01/17 12:20:26 by pwojnaro         ###   ########.fr       */
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
	int		i;
	int		j;
	char	current;
	int		player_found;

	player_found = 0;
	ft_printf("[DEBUG] Validating map boundaries...\n");
	if (!map || !map->grid)
	{
		ft_printf("[ERROR] Map structure or grid is NULL.\n");
		exit(1);
	}
	ft_printf("[DEBUG] Map dimensions - Height: %d, Width: %d\n",
		map->height, map->width);
	if (map->height < 3 || map->width < 3)
	{
		ft_printf("[ERROR] Invalid map dimensions. Height=%d, Width=%d\n",
			map->height, map->width);
		exit(1);
	}
	ft_printf("[DEBUG] Validating top wall...\n");
	validate_top_bottom_walls(map->grid[0], map->width, 1);
	ft_printf("[DEBUG] Validating bottom wall...\n");
	validate_top_bottom_walls(map->grid[map->height - 1], map->width, 0);
	for (i = 1; i < map->height - 1; i++)
	{
		ft_printf("[DEBUG] Validating row %d...\n", i);
		if (!map->grid[i])
		{
			ft_printf("[ERROR] Row %d is NULL.\n", i);
			exit(1);
		}
		validate_side_walls(map->grid[i], map->width);
		for (j = 1; j < map->width - 1; j++)
		{
			current = map->grid[i][j];
			if (current == 'N' || current == 'S' || current == 'E'
				|| current == 'W')
			{
				player_found++;
				ft_printf("[DEBUG] Player found at (%d, %d)\n", i, j);
				if (map->grid[i - 1][j] == ' ' || map->grid[i + 1][j] == ' ' ||
					map->grid[i][j - 1] == ' ' || map->grid[i][j + 1] == ' ')
				{
					ft_printf("Player at (%d, %d) is in invalid area.\n", i, j);
					exit(1);
				}
			}
		}
	}
	if (player_found == 0)
	{
		ft_printf("[ERROR] No player start position found on the map.\n");
		exit(1);
	}
	else if (player_found > 1)
	{
		ft_printf("[ERROR] Multiple player found on the map.\n");
		exit(1);
	}
	ft_printf("[DEBUG] Map and player positions validated successfully.\n");
}
