/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piotrwojnarowski <piotrwojnarowski@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 09:39:53 by piotrwojnar       #+#    #+#             */
/*   Updated: 2025/01/06 21:44:19 by piotrwojnar      ###   ########.fr       */
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
		printf("[ERROR] Map structure or map list is NULL.\n");
		exit(1);
	}
	temp = map->list;
	while (temp)
	{
		if (!temp->line || temp->line[0] == '\0')
		{
			printf("[ERROR] Invalid line detected at row %d.\n", rows);
			exit(1);
		}
		rows++;
		temp = temp->next;
	}
	printf("[DEBUG] Total rows in map list: %d\n", rows);
	map->grid = mem_alloc(mem, sizeof(char *) * (rows + 1));
	if (!map->grid)
	{
		printf("[ERROR] Failed to allocate memory for map grid.\n");
		exit(1);
	}
	temp = map->list;
	while (temp)
	{
		printf("[DEBUG] Moving Node %d to Grid Row %d...\n", i, i);
		if (!temp->line)
		{
			printf("[ERROR] NULL or invalid line detected at row %d.\n", i);
			exit(1);
		}
		map->grid[i] = ft_strdup_cub(temp->line, mem);
		if (!map->grid[i])
		{
			printf("[ERROR] Failed to duplicate map line at row %d.\n", i);
			exit(1);
		}
		printf("[DEBUG] Grid Row %d assigned: '%s'\n", i, map->grid[i]);
		i++;
		temp = temp->next;
	}
	map->grid[rows] = NULL;
	printf("[DEBUG] Map list successfully converted to grid array.\n");
}
