/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   can_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:34:17 by pwojnaro          #+#    #+#             */
/*   Updated: 2025/02/10 13:52:13 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

bool	check_direction(t_collision_data *data, int direction)
{
	int		neighbor_x;
	int		neighbor_y;
	float	margin;

	neighbor_x = data->grid_x;
	neighbor_y = data->grid_y;
	margin = data->new_x - data->grid_x;
	if (direction >= 2)
		margin = data->new_y - data->grid_y;
	if (direction == 0)
		neighbor_x -= 1;
	if (direction == 1)
		neighbor_x += 1;
	if (direction == 2)
		neighbor_y -= 1;
	if (direction == 3)
		neighbor_y += 1;
	if (direction == 1 || direction == 3)
		margin = 1.0f - margin;
	if (margin < COLLISION_MARGIN && is_wall(data->map, neighbor_x, neighbor_y))
		return (false);
	return (true);
}

bool	check_collision(t_collision_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (!check_direction(data, i))
			return (false);
		i++;
	}
	return (true);
}

bool	can_move_forward(t_config *config, t_map *map, float move_distance,
	float angle_offset)
{
	t_collision_data	data;

	data.map = map;
	data.new_x = config->player.x + cosf(config->player.angle + angle_offset)
		* move_distance;
	data.new_y = config->player.y + sinf(config->player.angle + angle_offset)
		* move_distance;
	data.grid_x = (int)data.new_x;
	data.grid_y = (int)data.new_y;
	data.margin_x = data.new_x - data.grid_x;
	data.margin_y = data.new_y - data.grid_y;
	if (is_wall(map, data.grid_x, data.grid_y))
		return (false);
	return (check_collision(&data));
}

void	update_player_position(t_config *config, t_map *map,
	float move_distance, float angle_offset)
{
	if (can_move_forward(config, map, move_distance, angle_offset))
	{
		config->player.x += cosf(config->player.angle + angle_offset)
			* move_distance;
		config->player.y += sinf(config->player.angle + angle_offset)
			* move_distance;
	}
	else
	{
		ft_printf("[DEBUG] Movement blocked: Collision detected.\n");
	}
}

void	player_move_handler(mlx_key_data_t keydata, void *param)
{
	t_config	*config;
	float		move_speed;
	float		rot_speed;

	move_speed = 0.3f;
	rot_speed = 0.3f;
	config = (t_config *)param;
	if (keydata.action != MLX_PRESS && keydata.action != MLX_REPEAT)
		return ;
	if (keydata.key == MLX_KEY_W)
		update_player_position(config, &config->map, move_speed, 0.0f);
	else if (keydata.key == MLX_KEY_S)
		update_player_position(config, &config->map, move_speed, M_PI);
	else if (keydata.key == MLX_KEY_A)
		update_player_position(config, &config->map, move_speed, -M_PI_2);
	else if (keydata.key == MLX_KEY_D)
		update_player_position(config, &config->map, move_speed, M_PI_2);
	else if (keydata.key == MLX_KEY_LEFT)
		config->player.angle -= rot_speed;
	else if (keydata.key == MLX_KEY_RIGHT)
		config->player.angle += rot_speed;
}
