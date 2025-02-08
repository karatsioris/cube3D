/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 12:50:39 by pwojnaro          #+#    #+#             */
/*   Updated: 2025/02/08 13:16:56 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTER_H
# define RAYCASTER_H

# include "cube3d.h"

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
	t_ray_data		ray;
	struct s_map	*map;
	struct s_config	*config;
	float			start_x;
	float			start_y;
	float			angle;
	int				h;
}	t_cast_data;

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

void		draw_vertical_line(mlx_image_t *img, int x, t_draw_params *params,
				uint32_t color);
void		draw_textured_vertical_line(mlx_image_t *img, int x,
				t_draw_params *params, t_texture_data *tex_data);
void		calculate_draw_parameters(int h, float perpWallDist,
				t_draw_params *params);
bool		cast_ray(t_cast_data *data);
void		init_step_and_side_distances(t_cast_data *data, t_ray_calc *calc);
bool		perform_dda(t_cast_data *data, t_ray_calc *calc);
float		compute_perpwalldist(t_cast_data *data, t_ray_calc *calc);

#endif
