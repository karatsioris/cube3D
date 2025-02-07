/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_boundary_val.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaratsi <kkaratsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 09:40:11 by piotrwojnar       #+#    #+#             */
/*   Updated: 2025/02/06 14:00:22 by kkaratsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	validate_top_bottom_walls(char *line, int width, int is_top)
{
	int		i;
	char	*wall_name;

	if (is_top)
		wall_name = "Top";
	else
		wall_name = "Bottom";
	ft_printf("[DEBUG] Validating %s wall: %s\n", wall_name, line);
	if (!line)
	{
		ft_printf("[ERROR] Line is NULL while %s wall.\n", wall_name);
		exit(1);
	}
	i = 0;
	while (i < width - 1)
	{
		if (line[i] != '1')
		{
			ft_printf("[ERROR] %s wall is not closed at index %d (value: %c)\n",
				wall_name, i, line[i]);
			exit(1);
		}
		i++;
	}
	ft_printf("[DEBUG] %s wall validated successfully.\n", wall_name);
}

void	validate_side_walls(char *line, int width)
{
	if (!line)
		exit(1);
	if (line[0] != '1' || line[width - 1] != '1')
		exit(1);
	ft_printf("[DEBUG] Side walls validated successfully.\n");
}

void	validate_outer_walls(t_map *map)
{
	int	i;

	if (!map || !map->grid)
		exit(1);
	if (map->height < 3 || map->width < 3)
		exit(1);
	validate_top_bottom_walls(map->grid[0], map->width, 1);
	validate_top_bottom_walls(map->grid[map->height - 1], map->width, 0);
	i = 1;
	while (i < map->height - 1)
	{
		if (!map->grid[i])
			exit(1);
		validate_side_walls(map->grid[i], map->width);
		i++;
	}
}

int	is_invalid_player_position(t_map *map, int i, int j)
{
	return (map->grid[i - 1][j] == ' ' || map->grid[i + 1][j] == ' ' ||
			map->grid[i][j - 1] == ' ' || map->grid[i][j + 1] == ' ');
}

void	validate_inner_map(t_map *map)
{
	int	i;
	int	j;
	int	player_found;

	i = 1;
	j = 0;
	player_found = 0;
	while (i < map->height - 1)
	{
		j = 1;
		while (j < map->width - 1)
		{
			if (ft_strchr("NSEW", map->grid[i][j]))
			{
				if (++player_found > 1 || is_invalid_player_position(map, i, j))
					exit(1);
			}
			j++;
		}
		i++;
	}
	if (!player_found)
		exit(1);
}
