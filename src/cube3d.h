/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 11:58:20 by piotrwojnar       #+#    #+#             */
/*   Updated: 2025/02/06 17:19:43 by pwojnaro         ###   ########.fr       */
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
# define COLLISION_MARGIN 0.1f
# define FOV 1.0471975512

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

typedef struct s_render_data
{
	mlx_t		*mlx;
	t_map		*map;
	t_config	*config;
	mlx_image_t	*img;
}	t_render_data;

typedef struct s_draw_params
{
	int	lineheight;
	int	drawstart;
	int	drawend;
}	t_draw_params;

typedef struct s_texture_data
{
	mlx_image_t	*texture;
	int			tex_width;
	int			tex_height;
	float		wallx;
}	t_texture_data;

typedef struct s_ray_data
{
	t_draw_params	draw_params;
	mlx_image_t		*texture;
	int				tex_width;
	int				tex_height;
	float			wallx;
	int				hit_side;
}	t_ray_data;

typedef struct s_cast_data
{
	t_ray_data	ray;
	t_map		*map;
	t_config	*config;
	float		start_x;
	float		start_y;
	float		angle;
	int			h;
}	t_cast_data;

typedef struct s_collision_data
{
	t_map	*map;
	float	new_x;
	float	new_y;
	int		grid_x;
	int		grid_y;
	float	margin_x;
	float	margin_y;
}	t_collision_data;

typedef struct s_ray_calc
{
	float	ray_dir_x;
	float	ray_dir_y;
	int		map_x;
	int		map_y;
	float	delta_dist_x;
	float	delta_dist_y;
	int		step_x;
	int		step_y;
	float	side_dist_x;
	float	side_dist_y;
	int		side;
}	t_ray_calc;

void		ft_error(int code);
void		validate_map(t_map *map);
void		validate_map_boundary(t_map *map);
void		mem_free_all(t_memory *mem);
void		*mem_alloc(t_memory *mem, size_t size);
bool		mem_init(t_memory *mem);
void		ft_clean(t_map *map, t_memory *mem, t_resources *res);
void		initialize_config(t_config *config);
void		cleanup_textures(t_resources *res, mlx_t *mlx);
void		cleanup_resources(t_resources *res, mlx_t *mlx);
void		validate_outer_walls(t_map *map);
void		validate_inner_map(t_map *map);
void		game_loop(t_map *map, t_config *config);
void		load_textures(t_resources *res, t_texture *textures, mlx_t *mlx,
				t_memory *mem);
bool		can_move_forward(t_config *config, t_map *map, float move_distance,
				float angle_offset);
bool		is_wall(t_map *map, int x, int y);
float		compute_perpwalldist(t_cast_data *data, t_ray_calc *calc);
bool		perform_dda(t_cast_data *data, t_ray_calc *calc);
void		init_step_and_side_distances(t_cast_data *data, t_ray_calc *calc);
bool		init_config_and_map(t_config *config, t_memory *mem,
				int argc, char **argv);
void		key_event_handler(mlx_key_data_t keydata, void *param);

/* -------------------   kkaratsi functions  ---------------------*/

void		draw_vertical_line(mlx_image_t *img, int x, t_draw_params *params,
				uint32_t color);
void		calculate_draw_parameters(int h, float perpWallDist,
				t_draw_params *params);
bool		cast_ray(t_cast_data *data);
void		render_scene(t_render_data *data, int window_height);
void		clear_image(mlx_image_t *img, uint32_t color);
void		player_move_handler(mlx_key_data_t keydata, void *param);
void		render_scene_wrapper(void *param);
void		draw_textured_vertical_line(mlx_image_t *img, int x,
				t_draw_params *params, t_texture_data *tex_data);

#endif
