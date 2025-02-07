/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   can_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaratsi <kkaratsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:34:17 by pwojnaro          #+#    #+#             */
/*   Updated: 2025/02/07 15:05:43 by kkaratsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

float	get_margin_x(float new_x, int grid_x, int direction)
{
	if (direction == -1)
		return (new_x - grid_x);
	if (direction == 1)
		return (1.0f - (new_x - grid_x));
	return (1.0f);
}

float	get_margin_y(float new_y, int grid_y, int direction)
{
	if (direction == -1)
		return (new_y - grid_y);
	if (direction == 1)
		return (1.0f - (new_y - grid_y));
	return (1.0f);
}

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
