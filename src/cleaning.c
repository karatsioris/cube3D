/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:26:29 by pwojnaro          #+#    #+#             */
/*   Updated: 2025/02/04 16:28:02 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	cleanup_grid(t_map *map)
{
	int	i;

	if (!map || !map->grid)
		return ;
	i = 0;
	while (i < map->height)
	{
		free(map->grid[i]);
		i++;
	}
	free(map->grid);
	map->grid = NULL;
}

void	cleanup_list(t_map *map)
{
	t_list	*temp;

	if (!map || !map->list)
		return ;
	while (map->list)
	{
		temp = map->list->next;
		free(map->list->line);
		free(map->list);
		map->list = temp;
	}
	map->list = NULL;
}

void	cleanup_map(t_map *map)
{
	if (!map)
		return ;
	if (map->mlx)
	{
		mlx_terminate(map->mlx);
		map->mlx = NULL;
	}
	cleanup_grid(map);
	cleanup_list(map);
}

void	ft_clean(t_map *map, t_memory *mem, t_resources *res)
{
	if (res && map && map->mlx)
		cleanup_resources(res, map->mlx);
	cleanup_map(map);
	if (mem)
		mem_free_all(mem);
	exit(0);
}
