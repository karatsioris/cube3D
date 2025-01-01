/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finding_direction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piotrwojnarowski <piotrwojnarowski@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 09:46:07 by piotrwojnar       #+#    #+#             */
/*   Updated: 2025/01/01 09:46:10 by piotrwojnar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parsing.h"

t_position	find_element(char **map, char element, int height, int width)
{
	t_position	pos;
	int			row;
	int			col;

	pos.row = -1;
	pos.col = -1;
	row = 0;
	while (row < height)
	{
		col = 0;
		while (col < width)
		{
			if (map[row][col] == element)
			{
				pos.row = row;
				pos.col = col;
				return (pos);
			}
			col++;
		}
		row++;
	}
	return (pos);
}