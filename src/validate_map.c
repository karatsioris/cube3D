/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piotrwojnarowski <piotrwojnarowski@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 09:53:32 by piotrwojnar       #+#    #+#             */
/*   Updated: 2025/01/01 15:40:34 by piotrwojnar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	count_map_elements(char *line, t_map *map)
{
	while (*line)
	{
		if (*line == 'N' || *line == 'S' || *line == 'E' || *line == 'W')
		{
			map->player_n++;
			if (map->player_n > 1)
				ft_error(-3);
		}
		else if (*line == '1')
			map->wall_n++;
		else if (*line == '0' || *line == ' ')
			;
		else
			ft_error(-5);
		line++;
	}
}

void	realloc_map(t_map *map)
{
	map->grid = (char **)ft_realloc(map->grid,
			map->current_row * sizeof(char *),
			(map->current_row + 1) * sizeof(char *));
	if (!map->grid)
	{
		free_map_lines(map, map->current_row);
		printf("Error: Memory allocation failed during map reallocation.\n");
		exit(1);
	}
}

void	process_line(t_map *map, char *line)
{
	int	i;

	i = 0;
	map->grid[map->current_row++] = line;
	while (line[i])
	{
		if (line[i] == 'P')
			map->player_n++;
		else if (line[i] == '1')
			map->wall_n++;
		i++;
	}
}

int	load_map(t_map *map, const char *path)
{
	map->path = strdup(path);
	if (!map->path)
		return (-1);
	map->fd = open(map->path, O_RDONLY);
	if (map->fd == -1)
	{
		free(map->path);
		return (-1);
	}
	validate_file_extension(map);
	close(map->fd);
	return (0);
}