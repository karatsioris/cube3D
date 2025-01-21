/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaratsi <kkaratsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 11:58:20 by piotrwojnar       #+#    #+#             */
/*   Updated: 2025/01/21 17:00:58 by kkaratsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define CUBE3D_H
#include <stdbool.h>
#include <stdlib.h>
#include <fcntl.h> 
#include "../lib/MLX42/include/MLX42/MLX42.h"
#include "libft/libft.h"
#include <stdio.h>
#include <math.h>

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
}	t_config;

typedef struct s_position
{
	int	row;
	int	col;
}	t_position;



int		load_map(t_map *map, const char *path);
void	ft_error(int code);
void	parse_texture(char *line, t_texture *textures);
void	parse_color(char *line, int color[3]);
void	process_line(t_map *map, char *line);
void	validate_file_extension(t_map *map);
void	free_map_lines(t_map *map, int rows);
void	validate_map(t_map *map);
void	realloc_map(t_map *map);

