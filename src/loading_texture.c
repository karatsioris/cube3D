/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:24:38 by pwojnaro          #+#    #+#             */
/*   Updated: 2025/02/10 12:40:19 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static mlx_texture_t	*validate_and_load_texture(char *path, mlx_t *mlx,
	t_resources *res)
{
	mlx_texture_t	*tex;

	if (path == NULL || *path == '\0')
	{
		ft_printf("[ERROR] Texture path is NULL or empty.\n");
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
		ft_printf("[ERROR] Failed to load texture from path: %s\n", path);
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
	int		i;
	char	*paths[4];

	paths[0] = textures->north;
	paths[1] = textures->south;
	paths[2] = textures->west;
	paths[3] = textures->east;
	res->texture_count = 4;
	res->images = mem_alloc(mem, sizeof(mlx_image_t *) * res->texture_count);
	if (!res->images)
		ft_texture_err("Failed to allocate memory for textures", -1, res, mlx);
	i = 0;
	while (i < res->texture_count)
	{
		if (paths[i] == NULL)
			ft_texture_err("Missing texture", i, res, mlx);
		res->images[i] = load_texture_for_path(paths[i], mlx, res);
		i++;
	}
	res->image_count = res->texture_count;
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
