/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:26:29 by pwojnaro          #+#    #+#             */
/*   Updated: 2025/02/06 17:21:01 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	cleanup_grid(t_map *map)
{
	map->grid = NULL;
}

void	cleanup_list(t_map *map)
{
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
	static int	cleaned = 0;

	printf("[DEBUG] Entering ft_clean...\n");
	if (!cleaned && res && map && map->mlx)
	{
		printf("[DEBUG] Calling cleanup_resources...\n");
		cleanup_resources(res, map->mlx);
		cleaned = 1;
	}
	printf("[DEBUG] Calling cleanup_map...\n");
	cleanup_map(map);
	if (mem)
	{
		printf("[DEBUG] Calling mem_free_all...\n");
		mem_free_all(mem);
	}
	printf("[DEBUG] Exiting ft_clean...\n");
	exit(0);
}
