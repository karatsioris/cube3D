/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_cleaning.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piotrwojnarowski <piotrwojnarowski@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 09:23:39 by piotrwojnar       #+#    #+#             */
/*   Updated: 2025/01/01 09:29:52 by piotrwojnar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parsing.h"

void	mlx_clean(t_map *map)
{
	if (map->mlx == NULL)
		return ;
	if (map->mlx->window != NULL)
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
		free_map_resources(map);
		free_img_grid(map);
		mlx_clean(map);
	}
	exit(0);
}

void	cleanup_resources(t_resources *res, mlx_t *mlx)
{
	int	i;

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