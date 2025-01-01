/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piotrwojnarowski <piotrwojnarowski@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 11:58:20 by piotrwojnar       #+#    #+#             */
/*   Updated: 2025/01/01 12:26:30 by piotrwojnar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define CUBE3D_H
#include <stdbool.h>
#include <stdlib.h>
#include <fcntl.h> 
#include "../lib/MLX42/include/MLX42/MLX42.h"

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
}	t_map;

typedef struct s_config
{
	t_texture	textures;
	t_color		colors;
	t_map		map;
	t_player	player;
	t_memory	*memory;
}	t_config;

