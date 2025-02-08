/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_boundary_val.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 09:40:11 by piotrwojnar       #+#    #+#             */
/*   Updated: 2025/02/08 15:38:00 by pwojnaro         ###   ########.fr       */
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
}

void	validate_side_walls(char *line, int width)
{
	if (!line)
		exit(1);
	if (line[0] != '1' || line[width - 2] != '1')
		exit(1);
}

void	validate_outer_walls(t_map *map)
{
	int	i;
	int	width;
	int	height;

	width = map->width;
	height = map->height;
	i = 0;
	while (i < width)
	{
		if (map->grid[0][i] != '1')
			ft_wall_err("Map is not enclosed at", i, "top row");
		if (map->grid[height - 1][i] != '1')
			ft_wall_err("Map is not enclosed at", i, "bottom row");
		i++;
	}
	i = 0;
	while (i < height)
	{
		if (map->grid[i][0] != '1')
			ft_wall_err("Map is not enclosed at", i, "left column");
		if (map->grid[i][width - 1] != '1')
			ft_wall_err("Map is not enclosed at", i, "right column");
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

	player_found = 0;
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (ft_strchr("NSEW", map->grid[i][j]))
			{
				if (++player_found > 1)
					ft_error(-4);
			}
			if (map->grid[i][j] == ' ')
				ft_error(-6);
			j++;
		}
		i++;
	}
	if (!player_found)
		ft_error(-2);
}
