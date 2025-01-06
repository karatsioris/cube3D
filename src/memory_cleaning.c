/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_cleaning.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piotrwojnarowski <piotrwojnarowski@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 09:23:39 by piotrwojnar       #+#    #+#             */
/*   Updated: 2025/01/06 16:40:54 by piotrwojnar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	cleanup_resources(t_resources *res, mlx_t *mlx)
{
	int	i;

	if (!res || !mlx)
		return ;
	ft_printf("[DEBUG] Cleaning up textures...\n");
	i = res->texture_count;
	while (i--)
	{
		if (res->textures[i])
		{
			mlx_delete_texture(res->textures[i]);
			res->textures[i] = NULL;
			ft_printf("[DEBUG] Deleted texture %d.\n", i);
		}
	}
	free(res->textures);
	res->textures = NULL;
	res->texture_count = 0;
	ft_printf("[DEBUG] Texture resources freed successfully.\n");
	ft_printf("[DEBUG] Cleaning up images...\n");
	i = res->image_count;
	while (i--)
	{
		if (res->images[i])
		{
			mlx_delete_image(mlx, res->images[i]);
			res->images[i] = NULL;
			ft_printf("[DEBUG] Deleted image %d.\n", i);
		}
	}
	free(res->images);
	res->images = NULL;
	res->image_count = 0;
	ft_printf("[DEBUG] Image resources freed successfully.\n");
}

void	cleanup_textures(t_resources *res, mlx_t *mlx)
{
	if (!res || !mlx)
	{
		ft_printf("[ERROR] cleanup_textures received NULL pointer.\n");
		return ;
	}
	ft_printf("[DEBUG] Cleaning up images...\n");
	for (int i = 0; i < res->image_count; i++)
	{
		if (res->images && res->images[i])
		{
			mlx_delete_image(mlx, res->images[i]);
			res->images[i] = NULL;
			ft_printf("[DEBUG] Deleted image %d.\n", i);
		}
	}
	if (res->images)
	{
		free(res->images);
		res->images = NULL;
	}
	res->image_count = 0;
	ft_printf("[DEBUG] All image resources freed successfully.\n");
}

void	ft_clean(t_map *map, t_memory *mem, t_resources *res)
{
	if (res && map && map->mlx)
	{
		cleanup_resources(res, map->mlx);
	}
	if (map && map->mlx)
	{
		mlx_terminate(map->mlx);
		map->mlx = NULL;
	}
	if (mem)
	{
		mem_free_all(mem);
	}
	ft_printf("[DEBUG] Resources and memory cleaned. Exiting...\n");
	exit(0);
}
