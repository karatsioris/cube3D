/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_cleaning.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 09:23:39 by piotrwojnar       #+#    #+#             */
/*   Updated: 2025/02/04 14:35:39 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	cleanup_resources(t_resources *res, mlx_t *mlx)
{
	int	i;

	if (!res || !mlx)
		return ;
	i = res->texture_count;
	while (i--)
	{
		if (res->textures[i])
		{
			mlx_delete_texture(res->textures[i]);
			res->textures[i] = NULL;
		}
	}
	free(res->textures);
	res->textures = NULL;
	res->texture_count = 0;
	i = res->image_count;
	while (i--)
	{
		if (res->images[i])
		{
			mlx_delete_image(mlx, res->images[i]);
			res->images[i] = NULL;
		}
	}
	free(res->images);
	res->images = NULL;
	res->image_count = 0;
}

void	cleanup_textures(t_resources *res, mlx_t *mlx)
{
	int	i;

	i = 0;
	if (!res || !mlx)
	{
		ft_printf("[ERROR] cleanup_textures received NULL pointer.\n");
		return ;
	}
	ft_printf("[DEBUG] Cleaning up images...\n");
	while (i < res->image_count)
	{
		if (res->images && res->images[i])
		{
			mlx_delete_image(mlx, res->images[i]);
			res->images[i] = NULL;
			ft_printf("[DEBUG] Deleted image %d.\n", i);
		}
		i++;
	}
	if (res->images)
	{
		free(res->images);
		res->images = NULL;
	}
	res->image_count = 0;
}

void	ft_clean(t_map *map, t_memory *mem, t_resources *res)
{
	t_list	*temp;
	int		i;

	i = 0;
	if (res && map && map->mlx)
	{
		cleanup_resources(res, map->mlx);
	}
	if (map)
	{
		if (map->mlx)
		{
			mlx_terminate(map->mlx);
			map->mlx = NULL;
		}
		if (map->grid)
		{
			while (i < map->height)
			{
				free(map->grid[i]);
				i++;
			}
			free(map->grid);
			map->grid = NULL;
		}
		if (map->list)
		{
			while (map->list)
			{
				temp = map->list->next;
				free(map->list->line);
				free(map->list);
				map->list = temp;
			}
			map->list = NULL;
		}
	}
	if (mem)
		mem_free_all(mem);
	exit(0);
}
