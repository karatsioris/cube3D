#include "Cube3d.h"

// #define MAP_ROW 6
// #define MAP_COLUMN 8
// #define Window_Width 800
// #define Window_Height 600

// // 0 = empty space
// // 1 = wall  
// // 2 = player
// float player_x = 2;
// float player_y = 2;

// int map[MAP_ROW][MAP_COLUMN] =
// {
//     {1, 1, 1, 1, 1, 1, 1, 1},
//     {1, 0, 0, 0, 0, 0, 0, 1},
//     {1, 0, 2, 0, 0, 0, 0, 1},
//     {1, 0, 0, 0, 0, 0, 0, 1},
//     {1, 0, 0, 0, 0, 0, 0, 1},
//     {1, 1, 1, 1, 1, 1, 1, 1},
// };

// void print_map()
// {
//     int x;
//     int y;
//     int P;

//     x = 0;
//     P = 2;
//     y = 0;
//     printf("   ");
//     while (y < MAP_COLUMN)
//     {
//         printf("%d", y);
//         y++;
//     }
//     printf("\n");
//     printf("\n");
//     while (x < MAP_ROW)
//     {
//         y = 0;
//         printf("%d  ", x);
//         while (y < MAP_COLUMN)
//         {
//             if (map[x][y] == P)
//                 printf("P");
//             else
//                 printf("%d", map[x][y]);
//             y++;
//         }
//         x++;
//         printf("\n");
//     }
//     printf("\n");
// }

// void calculate_draw_parameters(int h, float perpWallDist, int *lineHeight, int *drawStart, int *drawEnd)
// {
//     *lineHeight = (int)(h / perpWallDist);
//     *drawStart = -(*lineHeight) / 2 + h / 2;
//     if (*drawStart < 0)
//         *drawStart = 0;
//     *drawEnd = (*lineHeight) / 2 + h / 2;
//     if (*drawEnd >= h)
//         *drawEnd = h - 1;
//     printf("Line height: %d, drawStart: %d, drawEnd: %d\n", *lineHeight, *drawStart, *drawEnd);
// }

// bool cast_ray(float start_x, float start_y, float angle, int h, int *lineHeight, int *drawStart, int *drawEnd)
// {
//     float ray_dir_x = cos(angle);
//     float ray_dir_y = sin(angle);
//     float delta_dist_x = fabs(1 / ray_dir_x);
//     float delta_dist_y = fabs(1 / ray_dir_y);
//     float side_dist_x;
//     float side_dist_y;
//     int step_x;
//     int step_y;
//     int map_x = (int)start_x;
//     int map_y = (int)start_y;
//     int side;

//     if (ray_dir_x < 0)
//     {
//         step_x = -1;
//         side_dist_x = (start_x - map_x) * delta_dist_x;
//     }
//     else
//     {
//         step_x = 1;
//         side_dist_x = (map_x + 1.0 - start_x) * delta_dist_x;
//     }
//     if (ray_dir_y < 0)
//     {
//         step_y = -1;
//         side_dist_y = (start_y - map_y) * delta_dist_y;
//     }
//     else
//     {
//         step_y = 1;
//         side_dist_y = (map_y + 1.0 - start_y) * delta_dist_y;
//     }

//     while (map_x >= 0 && map_x < MAP_COLUMN && map_y >= 0 && map_y < MAP_ROW)
//     {
//         if (side_dist_x < side_dist_y)
//         {
//             side_dist_x += delta_dist_x;
//             map_x += step_x;
//             side = 0;
//         }
//         else
//         {
//             side_dist_y += delta_dist_y;
//             map_y += step_y;
//             side = 1;
//         }
//         if (map[map_y][map_x] == 1)
//         {
//             float perpWallDist;
//             if (side == 0)
//                 perpWallDist = (side_dist_x - delta_dist_x);
//             else
//                 perpWallDist = (side_dist_y - delta_dist_y);
//             calculate_draw_parameters(h, perpWallDist, lineHeight, drawStart, drawEnd);
//             return true;
//         }
//     }
//     return false;
// }

// void draw_vertical_line(mlx_image_t *img, int x, int drawStart, int drawEnd, uint32_t color)
// {
//     for (int y = drawStart; y < drawEnd; y++)
//     {
//         mlx_put_pixel(img, x, y, color);
//     }
// }

// int main(void)
// {
//     mlx_t *mlx;
//     mlx_image_t *img;
//     int lineHeight, drawStart, drawEnd;

//     mlx = mlx_init(Window_Width, Window_Height, "Cube3d", false);
//     if (!mlx)
//     {
//         printf("Error: mlx_init failed\n");
//         return 0;
//     }

//     img = mlx_new_image(mlx, Window_Width, Window_Height);
//     if (!img)
//     {
//         printf("Error: mlx_new_image failed\n");
//         return 0;
//     }

//     float angle = 0.785398; // 45 degrees in radians
//     if (cast_ray(player_x, player_y, angle, Window_Height, &lineHeight, &drawStart, &drawEnd))
//     {
//         draw_vertical_line(img, Window_Width / 2, drawStart, drawEnd, 0xFFFFFF); // Draw a vertical line in the middle of the screen
//     }

//     mlx_image_to_window(mlx, img, 0, 0);
//     mlx_loop(mlx);
//     return 0;
// }

#define MAP_ROW 10
#define MAP_COLUMN 10
#define Window_Width 1000
#define Window_Height 1000
#define FOV 3.14159 / 3

// 0 = empty space
// 1 = wall  
// 2 = player
float player_x = 3;
float player_y = 3;
float player_angle = 0;

int map[MAP_ROW][MAP_COLUMN] =
{
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 2, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1},
};

void calculate_draw_parameters(int h, float perpWallDist, int *lineHeight, int *drawStart, int *drawEnd)
{
    *lineHeight = (int)(h / perpWallDist);
    *drawStart = -(*lineHeight) / 2 + h / 2;
    if (*drawStart < 0)
        *drawStart = 0;
    *drawEnd = (*lineHeight) / 2 + h / 2;
    if (*drawEnd >= h)
        *drawEnd = h - 1;
    printf("Line height: %d, drawStart: %d, drawEnd: %d\n", *lineHeight, *drawStart, *drawEnd);
}

bool cast_ray(float start_x, float start_y, float angle, int h, int *lineHeight, int *drawStart, int *drawEnd)
{
    float ray_dir_x = cos(angle);
    float ray_dir_y = sin(angle);
    float delta_dist_x = fabs(1 / ray_dir_x);
    float delta_dist_y = fabs(1 / ray_dir_y);
    float side_dist_x;
    float side_dist_y;
    int step_x;
    int step_y;
    int map_x = (int)start_x;
    int map_y = (int)start_y;
    int side;

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
        if (map[map_y][map_x] == 1)
        {
            float perpWallDist;
            if (side == 0)
                perpWallDist = (side_dist_x - delta_dist_x);
            else
                perpWallDist = (side_dist_y - delta_dist_y);
            calculate_draw_parameters(h, perpWallDist, lineHeight, drawStart, drawEnd);
            return true;
        }
    }
    return false;
}

void draw_vertical_line(mlx_image_t *img, int x, int drawStart, int drawEnd, uint32_t color)
{
    for (int y = drawStart; y < drawEnd; y++)
    {
        mlx_put_pixel(img, x, y, color);
    }
}

void clear_image(mlx_image_t *img, uint32_t color)
{
    for (uint32_t y = 0; y < img->height; y++)
    {
        for (uint32_t x = 0; x < img->width; x++)
        {
            mlx_put_pixel(img, x, y, color);
        }
    }
}

// void render_scene(mlx_t *mlx, mlx_image_t *img)
// {
//     int lineHeight, drawStart, drawEnd;
//     clear_image(img, 0x0C0604FF);
//     if (cast_ray(player_x, player_y, player_angle, Window_Height, &lineHeight, &drawStart, &drawEnd))
//     {
//         draw_vertical_line(img, Window_Width/2, drawStart, drawEnd, 0xFFFFFFFF); // Draw a vertical line in the middle of the screen
//     }
//     mlx_image_to_window(mlx, img, 0, 0);
// }

void render_scene(mlx_t *mlx, mlx_image_t *img)
{
    int y, x, lineHeight, drawStart, drawEnd;


    // Clear the image with a black color
    clear_image(img, 0x000000);

    // Loop through each vertical stripe of the screen
    x = 0;
    while (x < Window_Width)
    {
        // Cast a ray from the player's position and angle
        if (cast_ray(player_x, player_y, player_angle + (x - Window_Width / 2) * (FOV / Window_Width), Window_Height, &lineHeight, &drawStart, &drawEnd))
        {
            // Draw the ceiling
            y = 0;
            while (y < drawStart)
            {
                mlx_put_pixel(img, x, y, 0x89CFF3FF); // Light blue color for ceiling
                y++;
            }

            // Draw the wall
            draw_vertical_line(img, x, drawStart, drawEnd, 0xFFFFFF); // White color for wall

            // Draw the floor
            y = drawEnd;
            while (y < Window_Height)
            {
                mlx_put_pixel(img, x, y, 0xB99470FF); // Brown color for floor
                y++;
            }
        }
        x++;
    }
    // Display the image in the window
    mlx_image_to_window(mlx, img, 0, 0);
}


void key_hook(mlx_key_data_t keydata, void *param)
{
    mlx_t *mlx = (mlx_t *)param;
    mlx_image_t *img = mlx_new_image(mlx, Window_Width, Window_Height);
    if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
    {
        switch (keydata.key)
        {
            case MLX_KEY_W:
                player_x += 0.1;
                break;
            case MLX_KEY_S:
                player_x -= 0.1;
                break;
            case MLX_KEY_A:
                player_y -= 0.1;
                break;
            case MLX_KEY_D:
                player_y += 0.1;
                break;
            case MLX_KEY_LEFT:
                player_angle -= 0.1;
                break;
            case MLX_KEY_RIGHT:
                player_angle += 0.1;
                break;
            default:
                break;
        }
        render_scene(mlx, img);
        printf("\nPlayer position: x = %f, y = %f angle = %f\n", player_x, player_y, player_angle);
    }
}

// void key_hook(mlx_key_data_t keydata, void *param)
// {
//     mlx_t *mlx = (mlx_t *)param;
//     mlx_image_t *img = mlx_new_image(mlx, Window_Width, Window_Height);
//     float moveSpeed = 0.1;
//     float rotSpeed = 0.1;

//     if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
//     {
//         switch (keydata.key)
//         {
//             case MLX_KEY_W:
//                 if (map[(int)(player_y - sin(player_angle) * moveSpeed)][(int)player_x] == 0)
//                     player_y -= sin(player_angle) * moveSpeed;
//                 if (map[(int)player_y][(int)(player_x + cos(player_angle) * moveSpeed)] == 0)
//                     player_x += cos(player_angle) * moveSpeed;
//                 break;
//             case MLX_KEY_S:
//                 if (map[(int)(player_y + sin(player_angle) * moveSpeed)][(int)player_x] == 0)
//                     player_y += sin(player_angle) * moveSpeed;
//                 if (map[(int)player_y][(int)(player_x - cos(player_angle) * moveSpeed)] == 0)
//                     player_x -= cos(player_angle) * moveSpeed;
//                 break;
//             case MLX_KEY_A:
//                 player_angle -= rotSpeed;
//                 break;
//             case MLX_KEY_D:
//                 player_angle += rotSpeed;
//                 break;
//             case MLX_KEY_LEFT:
//                 player_angle -= rotSpeed;
//                 break;
//             case MLX_KEY_RIGHT:
//                 player_angle += rotSpeed;
//                 break;
//             default:
//                 break;
//         }
//         render_scene(mlx, img);
//         printf("\nPlayer position: x = %f, y = %f angle = %f\n", player_x, player_y, player_angle);
//     }
// }


int main(void)
{
    mlx_t *mlx;
    mlx_image_t *img;

    mlx = mlx_init(Window_Width, Window_Height, "Cube3d", false);
    if (!mlx)
    {
        printf("Error: mlx_init failed\n");
        return 0;
    }

    img = mlx_new_image(mlx, Window_Width, Window_Height);
    if (!img)
    {
        printf("Error: mlx_new_image failed\n");
        return 0;
    }

    mlx_key_hook(mlx, key_hook, mlx);
    render_scene(mlx, img);
    mlx_loop(mlx);
    return 0;
}
