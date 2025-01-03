/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaratsi <kkaratsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 12:23:56 by piotrwojnar       #+#    #+#             */
/*   Updated: 2025/01/03 12:18:18 by kkaratsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

// int	main(void)
// {
// 	mlx_t	*mlx;
// 	// mlx_image_t	*img;
	
// 	mlx	= mlx_init(500, 500, "Cube3d", false);
// 	if (!mlx)
// 	{
// 		printf("Error: mlx_init failed\n");
// 		return (0);
// 	}
// 	mlx_loop(mlx);
// 	return (0);
// }

#include <stdio.h>
#include <math.h>

#define MAP_ROW 5
#define MAP_COLUMN 6

// 0 = empty space
// 1 = wall  
// 2 = player
float player_x = 2.5;
float player_y = 2.5;

int map [MAP_ROW][MAP_COLUMN] =
{
    {1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 1},
    {1, 0, 2, 0, 0, 1},
    {1, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1},
};

void print_map()
{
    int x;
    int y;
    int P;

    x = 0;
    P = 2;
    y = 0;
    printf("   ");
    while (y < MAP_COLUMN)
    {
        printf("%d", y);
        y++;
    }
    printf("\n");
    printf("\n");
    while (x < MAP_ROW)
    {
        y = 0;
        printf("%d  ", x);
        while (y < MAP_COLUMN)
        {
            if (map[x][y] == P)
                printf("P");
            else
                printf("%d", map[x][y]);
            y++;
        }
        x++;
        printf("\n");
    }
    printf("\n");
}

bool cast_horizontal_ray(float start_x, float start_y, float angle)
{
    float x;
    float y;
    float x_step;
    float y_step;

    x = start_x;
    y = start_y;
    x_step = cos(angle);
    y_step = sin(angle);
    
    printf("\nStarting ray at (%f, %f) with angle %f\n", x, y, angle);
    printf("Ray direction: x_step = %f, y_step = %f\n\n", x_step, y_step);
    while (x >= 0 && x < MAP_COLUMN && y >= 0 && y < MAP_ROW)
    {
        printf("Checking coordinates: (%f, %f) -> map[%d][%d] = %d\n", x, y, (int)y, (int)x, map[(int)y][(int)x]);
        if (map[(int)y][(int)x] == 1)
            return (true);
        x += x_step;
        y += y_step;
    }
    return (false);
}

bool cast_vertical_ray(float start_x, float start_y, float angle)
{
    float x;
    float y;
    float x_step;
    float y_step;

    x = start_x;
    y = start_y;
    x_step = sin(angle);
    y_step = cos(angle);
    
    printf("\nStarting ray at (%f, %f) with angle %f\n", x, y, angle);
    printf("Ray direction: x_step = %f, y_step = %f\n\n", x_step, y_step);
    while (x >= 0 && x < MAP_ROW && y >= 0 && y < MAP_COLUMN)
    {
        printf("Checking coordinates: (%f, %f) -> map[%d][%d] = %d\n", x, y, (int)y, (int)x, map[(int)y][(int)x]);
        if (map[(int)y][(int)x] == 1)
            return (true);
        x += x_step;
        y += y_step;
    }
    return (false);
}

int main (void)
{
    print_map();
    printf("\nHorizontal Ray hit wall: %d\n", cast_horizontal_ray(player_x, player_y, 0));
    printf("\nVertical Ray hit wall: %d\n", cast_vertical_ray(player_x, player_y, 0));

    return (0);
}