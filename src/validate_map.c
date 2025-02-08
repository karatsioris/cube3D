/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 09:53:32 by piotrwojnar       #+#    #+#             */
/*   Updated: 2025/02/08 12:34:15 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	put_on_list(const char *line, t_list **list, t_memory *mem)
{
	t_list	*node;
	t_list	*temp;

	if (!line || *line == '\0' || *line == '\n')
		return (0);
	node = mem_alloc(mem, sizeof(t_list));
	if (!node)
		return (0);
	node->line = ft_strdup_cub(line, mem);
	if (!node->line || node->line[0] == '\0')
		return (0);
	node->next = NULL;
	if (!(*list))
		*list = node;
	else
	{
		temp = *list;
		while (temp->next)
			temp = temp->next;
		temp->next = node;
	}
	return (1);
}

int	calculate_map_dimensions(char **grid, int *height, int *width)
{
	int	max_width;
	int	row_count;
	int	row_length;
	int	i;

	max_width = 0;
	row_count = 0;
	i = 0;
	if (!grid || !height || !width)
	{
		return (-1);
	}
	while (grid[i] != NULL)
	{
		row_count++;
		row_length = strlen(grid[i]);
		if (row_length > max_width)
			max_width = row_length;
		i++;
	}
	*height = row_count;
	*width = max_width;
	if (*height == 0 || *width == 0)
		return (-1);
	return (0);
}

void	validate_map(t_map *map)
{
	if (calculate_map_dimensions(map->grid, &map->height, &map->width) != 0)
	{
		ft_printf("[ERROR] Failed to calculate map dimensions.\n");
		exit(1);
	}
	validate_map_boundary(map);
}

void	validate_map_boundary(t_map *map)
{
	validate_outer_walls(map);
	validate_inner_map(map);
}
