/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piotrwojnarowski <piotrwojnarowski@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 09:39:53 by piotrwojnar       #+#    #+#             */
/*   Updated: 2025/01/06 16:36:14 by piotrwojnar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	list_to_array(t_map *map, t_memory *mem)
{
	int		i;
	int		rows;
	t_list	*temp;

	i = 0;
	rows = 0;
	if (!map || !map->list)
	{
		ft_printf("[ERROR] Map structure or map list is NULL.\n");
		exit(1);
	}
	temp = map->list;
	while (temp)
	{
		if (!temp->line || temp->line[0] == '\0' || temp->line[0] == '\n')
		{
			ft_printf("[ERROR] Invalid or empty line detected in the map list at row %d.\n", rows);
			exit(1);
		}
		rows++;
		temp = temp->next;
	}
	ft_printf("[DEBUG] Total rows in map list: %d\n", rows);
	map->grid = mem_alloc(mem, sizeof(char *) * (rows + 1));
	if (!map->grid)
	{
		ft_printf("[ERROR] Failed to allocate memory for map grid.\n");
		exit(1);
	}
	temp = map->list;
	while (temp)
	{
		if (!temp->line || temp->line[0] == '\0')
		{
			ft_printf("[ERROR] NULL or invalid line detected at row %d.\n", i);
			exit(1);
		}
		map->grid[i] = ft_strdup_cub(temp->line, mem);
		if (!map->grid[i])
		{
			ft_printf("[ERROR] Failed to duplicate map line at row %d.\n", i);
			exit(1);
		}
		ft_printf("[DEBUG] Grid Row %d: '%s'\n", i, map->grid[i]);
		i++;
		temp = temp->next;
	}
	map->grid[rows] = NULL;
	ft_printf("[DEBUG] Map list successfully converted to grid array.\n");
}
