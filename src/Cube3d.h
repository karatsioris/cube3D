/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piotrwojnarowski <piotrwojnarowski@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 11:58:20 by piotrwojnar       #+#    #+#             */
/*   Updated: 2025/01/06 11:36:31 by piotrwojnar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
#define CUBE3D_H
#include <stdbool.h>
#include <stdlib.h>
#include <fcntl.h> 
#include "../lib/MLX42/include/MLX42/MLX42.h"
#include "libft/libft.h"
#include <stdio.h>
#include <errno.h>

#define	WINDOW_WIDTH 800
#define	WINDOW_HEIGHT 600
#define INITIAL_MEM_CAPACITY 10

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
}	t_color;

typedef struct s_player
{
	int		x;
	int		y;
	char	direction;
}	t_player;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		fd;
	char	*path;
	int		current_row;
	int		player_n;
	int		wall_n;
	mlx_t	*mlx;
	t_list	*list;
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
}	t_config;

typedef struct s_position
{
	int	row;
	int	col;
}	t_position;

void	ft_error(int code);
void	parse_texture(char *line, t_texture *textures);
void	parse_color(char *line, int color[3]);
void	process_line(t_map *map, t_memory *mem, char *line);
void	validate_file_extension(t_map *map);
void	validate_map(t_map *map, t_memory *mem);
void	validate_map_boundary(t_map *map);
void	validate_textures_and_colors(t_config *config);
void	initialize_player(t_config *config, t_map *map);
void	validate_args_and_load_map(int argc, char **argv, t_config *config,
			t_memory *mem);
void	mem_free_all(t_memory *mem);
void	*mem_alloc(t_memory *mem, size_t size);
bool	mem_init(t_memory *mem);
void	ft_clean(t_map *map, t_memory *mem);
void	parse_line(char *line, t_config *config, t_memory *mem,
			bool *is_parsing_map);
void	parse_cub_file(t_config *config, t_memory *mem, char *file_path);
void	list_to_array(t_map *map, t_memory *mem);
void	cleanup_resources(t_resources *res, mlx_t *mlx);
int		has_valid_extension(const char *path, const char *extension);

#endif