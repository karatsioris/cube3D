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

#include "Cube3d.h"

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
float player_x = 2;
float player_y = 2;

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

// bool cast_horizontal_ray(float start_x, float start_y, float angle)
// {
//     float x;
//     float y;
//     float x_step;
//     float y_step;

//     x = start_x;
//     y = start_y;
//     x_step = cos(angle);
//     y_step = sin(angle);
    
//     printf("\nStarting ray at (%f, %f) with angle %f\n", x, y, angle);
//     printf("Ray direction: x_step = %f, y_step = %f\n\n", x_step, y_step);
//     while (x >= 0 && x < MAP_COLUMN && y >= 0 && y < MAP_ROW)
//     {
//         printf("Checking coordinates: (%f, %f) -> map[%d][%d] = %d\n", x, y, (int)y, (int)x, map[(int)y][(int)x]);
//         if (map[(int)y][(int)x] == 1)
//             return (true);
//         x += x_step;
//         y += y_step;
//     }
//     return (false);
// }

bool	cast_horizontal_ray(float start_x, float start_y, float angle)
{
	float ray_dir_x;
	float ray_dir_y;
	float delta_dist_x;
	float delta_dist_y;
	float side_dist_x;
	float side_dist_y;
	int step_x;
	int step_y;
	int map_x;
	int map_y;

	ray_dir_x = cos(angle);
	ray_dir_y = sin(angle);
	delta_dist_x = fabs(1 / ray_dir_x);
	delta_dist_y = fabs(1 / ray_dir_y);
	map_x = (int)start_x;
	map_y = (int)start_y;
	int side;
	if (ray_dir_x == 0)
		delta_dist_x = 0;
	if (ray_dir_y == 0)
		delta_dist_y = 0;
	if (ray_dir_x == 0 && ray_dir_y == 0)
	{
		printf("Error: ray direction is 0\n");
		return (false);
	}
	if (ray_dir_x < 0)
	{
		step_x = -1;
		side_dist_x = (start_x - map_x) * delta_dist_x;
	}
	else
	{
		step_x = 1;
		side_dist_x = (map_x + 1.0 - start_x) * delta_dist_x;
	}
	if (ray_dir_y < 0)
	{
		step_y = -1;
		side_dist_y = (start_y - map_y) * delta_dist_y;
	}
	else
	{
		step_y = 1;
		side_dist_y = (map_y + 1.0 - start_y) * delta_dist_y;
	}
	printf("\nStarting ray at (%f, %f) with angle %f\n", start_x, start_y, angle);
    printf("Ray direction: ray_dir_x = %f, ray_dir_y = %f\n", ray_dir_x, ray_dir_y);
	while (map_x >= 0 && map_x < MAP_COLUMN && map_y >= 0 && map_y < MAP_ROW)
	{
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			map_x += step_x;
			side = 0;
		}
		else
		{
			side_dist_y += delta_dist_y;
			map_y += step_y;
			side = 1;
		}
		 printf("Current map position: (%d, %d), side: %d\n", map_y, map_x, side);
		if (map[map_x][map_y] == 1)
			return (true);
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
    // printf("\nVertical Ray hit wall: %d\n", cast_vertical_ray(player_x, player_y, 0));

    return (0);
}