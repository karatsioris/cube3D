/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_cleaning.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piotrwojnarowski <piotrwojnarowski@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 09:23:39 by piotrwojnar       #+#    #+#             */
/*   Updated: 2025/01/01 15:49:29 by piotrwojnar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	mlx_clean(t_map *map)
{
	if (!map || !map->mlx)
		return ;

	if (map->mlx->window)
	{
		mlx_close_window(map->mlx);
		map->mlx->window = NULL;
	}
	mlx_terminate(map->mlx);
	map->mlx = NULL;
}

void	ft_clean(t_map *map)
{
	if (map != NULL)
	{
		mlx_clean(map);
	}
	exit(0);
}

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
}

void	free_map_lines(t_map *map, int rows)
{
	int	i;

	i = 0;
	if (!map->grid)
		return ;
	while (i < rows)
	{
		free(map->grid[i]);
		i++;
	}
	free(map->grid);
	map->grid = NULL;
}