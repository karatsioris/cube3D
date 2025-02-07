/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_cleaning.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 09:23:39 by piotrwojnar       #+#    #+#             */
/*   Updated: 2025/02/06 17:25:36 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	cleanup_texture(t_resources *res)
{
	int	i;

	if (!res || !res->textures)
		return ;
	i = res->texture_count;
	while (i > 0)
	{
		i--;
		if (res->textures[i])
		{
			mlx_delete_texture(res->textures[i]);
			res->textures[i] = NULL;
		}
	}
	res->textures = NULL;
	res->texture_count = 0;
}

void	cleanup_images(t_resources *res, mlx_t *mlx)
{
	int	i;

	if (!res || !res->images)
		return ;
	printf("[DEBUG] Cleaning up images...\n");
	i = res->image_count;
	while (i > 0)
	{
		i--;
		if (res->images[i])
		{
			mlx_delete_image(mlx, res->images[i]);
			res->images[i] = NULL;
		}
	}
	res->image_count = 0;
}

void	cleanup_resources(t_resources *res, mlx_t *mlx)
{
	int	i;

	if (!res || !mlx)
		return ;
	i = 0;
	while (res->textures && i < res->texture_count)
	{
		if (res->textures[i])
			mlx_delete_texture(res->textures[i]);
		res->textures[i++] = NULL;
	}
	i = 0;
	while (res->images && i < res->image_count)
	{
		if (res->images[i])
			mlx_delete_image(mlx, res->images[i]);
		res->images[i++] = NULL;
	}
}

void	cleanup_textures(t_resources *res, mlx_t *mlx)
{
	int	i;

	i = 0;
	if (!res || !mlx)
		return ;
	while (i < res->image_count)
	{
		if (res->images && res->images[i])
		{
			mlx_delete_image(mlx, res->images[i]);
			res->images[i] = NULL;
		}
		i++;
	}
	if (res->images)
	{
		res->images = NULL;
	}
	res->image_count = 0;
}
