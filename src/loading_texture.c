/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:24:38 by pwojnaro          #+#    #+#             */
/*   Updated: 2025/02/06 15:49:13 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static mlx_texture_t	*validate_and_load_texture(char *path, mlx_t *mlx,
	t_resources *res)
{
	mlx_texture_t	*tex;

	if (path == NULL)
	{
		ft_printf("[ERROR] Texture path is NULL.\n");
		cleanup_textures(res, mlx);
		exit(1);
	}
	if (access(path, F_OK) == -1)
	{
		perror("[ERROR] File does not exist or cannot be accessed");
		cleanup_textures(res, mlx);
		exit(1);
	}
	tex = mlx_load_png(path);
	if (tex == NULL)
	{
		cleanup_textures(res, mlx);
		exit(1);
	}
	return (tex);
}

static mlx_image_t	*load_texture_for_path(char *path, mlx_t *mlx,
	t_resources *res)
{
	mlx_texture_t	*tex;
	mlx_image_t		*image;

	tex = validate_and_load_texture(path, mlx, res);
	image = mlx_texture_to_image(mlx, tex);
	if (image == NULL)
	{
		mlx_delete_texture(tex);
		cleanup_textures(res, mlx);
		exit(1);
	}
	mlx_delete_texture(tex);
	return (image);
}

void	load_textures(t_resources *res, t_texture *textures, mlx_t *mlx,
	t_memory *mem)
{
	int				count;
	int				i;
	char			*paths[4];

	paths[0] = textures->north;
	paths[1] = textures->south;
	paths[2] = textures->west;
	paths[3] = textures->east;
	count = 4;
	i = 0;
	res->texture_count = count;
	res->images = mem_alloc(mem, sizeof(mlx_image_t *) * count);
	if (res->images == NULL)
	{
		ft_printf("[ERROR] Failed to allocate memory for images.\n");
		cleanup_textures(res, mlx);
		exit(1);
	}
	while (i < count)
	{
		res->images[i] = load_texture_for_path(paths[i], mlx, res);
		i++;
	}
	res->image_count = count;
}

void	render_scene_wrapper(void *param)
{
	t_render_data	*data;

	data = (t_render_data *)param;
	render_scene(data, WINDOW_HEIGHT);
}

void	key_event_handler(mlx_key_data_t keydata, void *param)
{
	(void)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		ft_printf("[DEBUG] ESC key pressed. Closing window...\n");
		exit(0);
	}
	else
	{
		player_move_handler(keydata, param);
	}
}
