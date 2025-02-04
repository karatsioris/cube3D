/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 11:58:20 by piotrwojnar       #+#    #+#             */
/*   Updated: 2025/02/04 17:31:56 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H
# include <stdbool.h>
# include <stdlib.h>
# include <fcntl.h> 
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "libft/libft.h"
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <math.h>

# define WINDOW_WIDTH 1200
# define WINDOW_HEIGHT 1000
# define INITIAL_MEM_CAPACITY 10
# define FOV 3.14159 / 3

typedef struct s_memory
{
	void	**allocated_pointers;
	size_t	count;
	size_t	capacity;
}	t_memory;

typedef struct s_texture
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
}	t_texture;

typedef struct s_color
{
	int	floor[3];
	int	ceiling[3];
	int	wall[3];
}	t_color;

typedef struct s_player
{
	float		x;
	float		y;
	char		direction;
	float		angle;
}	t_player;

typedef struct s_config	t_config;

typedef struct s_map
{
	char		**grid;
	int			width;
	int			height;
	int			fd;
	char		*path;
	int			current_row;
	int			player_n;
	int			wall_n;
	mlx_t		*mlx;
	t_list		*list;
	t_config	*config;
}	t_map;

typedef struct s_resources
{
	mlx_texture_t	**textures;
	int				texture_count;
	mlx_image_t		**images;
	int				image_count;
}	t_resources;

typedef struct s_config
{
	t_texture	textures;
	t_color		colors;
	t_map		map;
	t_player	player;
	t_memory	*memory;
	t_resources	resources;
	bool		use_textures;
	mlx_image_t	*img;
}	t_config;

void	ft_error(int code);
void	validate_map(t_map *map);
void	validate_map_boundary(t_map *map);
void	mem_free_all(t_memory *mem);
void	*mem_alloc(t_memory *mem, size_t size);
bool	mem_init(t_memory *mem);
void	ft_clean(t_map *map, t_memory *mem, t_resources *res);
void	initialize_config(t_config *config);
void	cleanup_textures(t_resources *res, mlx_t *mlx);
void	cleanup_resources(t_resources *res, mlx_t *mlx);
void	validate_outer_walls(t_map *map);
void	validate_inner_map(t_map *map);
void	game_loop(t_map *map, t_config *config);
void	load_textures(t_resources *res, t_texture *textures, mlx_t *mlx,
			t_memory *mem);

/* -------------------   kkaratsi functions  ---------------------*/

void	draw_vertical_line(mlx_image_t *img, int x, int drawStart, int drawEnd,
			uint32_t color);
void	calculate_draw_parameters(int h, float perpWallDist, int *lineHeight,
			int *drawStart, int *drawEnd);
bool	cast_ray(float start_x, float start_y, float angle, int h,
			int *lineHeight, int *drawStart, int *drawEnd, float *wallX,
			int *hit_side, t_map *map, t_config *config);
void	render_scene(mlx_t *mlx, t_map *map, t_config *config,
			int window_height, mlx_image_t *img);
void	clear_image(mlx_image_t *img, uint32_t color);
void	player_move_handler(mlx_key_data_t keydata, void *param);
void	render_scene_wrapper(void *param);

#endif
