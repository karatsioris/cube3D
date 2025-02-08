/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:26:29 by pwojnaro          #+#    #+#             */
/*   Updated: 2025/02/08 12:41:47 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	cleanup_map(t_map *map)
{
	if (!map)
		return ;
	if (map->mlx)
	{
		mlx_terminate(map->mlx);
		map->mlx = NULL;
	}
	map->grid = NULL;
	map->list = NULL;
}

void	ft_clean(t_map *map, t_memory *mem, t_resources *res)
{
	static int	cleaned = 0;

	if (!cleaned && res && map && map->mlx)
	{
		printf("[DEBUG] Calling cleanup_resources...\n");
		cleanup_resources(res, map->mlx);
		cleaned = 1;
	}
	cleanup_map(map);
	if (mem)
	{
		printf("[DEBUG] Calling mem_free_all...\n");
		mem_free_all(mem);
	}
	printf("[DEBUG] Exiting ft_clean...\n");
	exit(0);
}
