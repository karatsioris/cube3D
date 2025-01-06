/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piotrwojnarowski <piotrwojnarowski@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 09:39:53 by piotrwojnar       #+#    #+#             */
/*   Updated: 2025/01/06 12:56:26 by piotrwojnar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	list_to_array(t_map *map, t_memory *mem)
{
	int		i;
	t_list	*temp;
	int		rows;

	i = 0;
	rows = 0;
	if (!map->list)
	{
		ft_printf("[ERROR] No map lines to convert to array.\n");
		exit(1);
	}
	temp = map->list;
	while (temp)
	{
		if (!temp->content)
		{
			ft_printf("[ERROR] NULL node in the map list at index %d.\n", rows);
			exit(1);
		}
		rows++;
		temp = temp->next;
	}
	ft_printf("[DEBUG] Total Rows in Map List: %d\n", rows);
	map->grid = mem_alloc(mem, sizeof(char *) * (rows + 1));
	if (!map->grid)
	{
		ft_printf("[ERROR] Failed to allocate memory for map grid.\n");
		exit(1);
	}
	temp = map->list;
	while (temp)
	{
		if (!temp->content)
		{
			ft_printf("[ERROR] NULL content copy to grid at row %d.\n", i);
			exit(1);
		}
		map->grid[i] = ft_strdup_cub(temp->content, mem);
		if (!map->grid[i])
		{
			ft_printf("[ERROR] Failed to copy map line at row %d.\n", i);
			exit(1);
		}
		ft_printf("[DEBUG] Grid Row %d: %s\n", i, map->grid[i]);
		i++;
		temp = temp->next;
	}
	map->grid[i] = NULL;
	ft_printf("[DEBUG] Map list successfully converted to grid array.\n");
}
