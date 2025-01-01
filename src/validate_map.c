/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piotrwojnarowski <piotrwojnarowski@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 09:53:32 by piotrwojnar       #+#    #+#             */
/*   Updated: 2025/01/01 09:58:03 by piotrwojnar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

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
	map->map = (char **)ft_realloc(map->map,
			map->current_row * sizeof(char *),
			(map->current_row + 1) * sizeof(char *));
	if (!map->map)
	{
		free_map_lines(map, map->current_row);
		ft_error(-2);
	}
}

void	process_line(t_map *map, char *line)
{
	if (line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	map->map[map->current_row++] = line;
	count_map_elements(line, map);
}
