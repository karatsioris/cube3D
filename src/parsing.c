/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 09:39:53 by piotrwojnar       #+#    #+#             */
/*   Updated: 2025/01/19 12:39:32 by pwojnaro         ###   ########.fr       */
=======
/*   By: kkaratsi <kkaratsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 09:39:53 by piotrwojnar       #+#    #+#             */
/*   Updated: 2025/01/30 10:41:20 by kkaratsi         ###   ########.fr       */
>>>>>>> 65ac913c6d78f2c2c50a27b7732a73cd95b0ef02
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	get_map_dimensions(t_map *map);

void	list_to_array(t_map *map, t_memory *mem)
{
	int		i;
	int		len;
	int		rows;
	t_list	*temp;
	char	*line;

	i = 0;
	rows = 0;
	temp = map->list;
	while (temp)
	{
		rows++;
		temp = temp->next;
	}
<<<<<<< HEAD
=======
	printf("[DEBUG] Total rows in map list: %d\n", rows);
	map->height = rows;
>>>>>>> 65ac913c6d78f2c2c50a27b7732a73cd95b0ef02
	map->grid = mem_alloc(mem, sizeof(char *) * (rows + 1));
	if (!map->grid)
	{
		printf("[ERROR] Failed to allocate memory for map grid.\n");
		exit(1);
	}
	temp = map->list;
	while (temp)
	{
		line = ft_strdup_cub(temp->line, mem);
		if (!line)
		{
			printf("[ERROR] Failed to duplicate map line.\n");
			exit(1);
		}
		len = strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		map->grid[i++] = line;
		temp = temp->next;
	}
	map->grid[rows] = NULL;
<<<<<<< HEAD
=======
	printf("[DEBUG] Map list successfully converted to grid array.\n");
	// Set map width based on the longest line --- i add it
    for (i = 0; i < rows; i++)
    {
        int line_length = strlen(map->grid[i]);
        if (line_length > map->width)
        {
            map->width = line_length;
        }
    }
    printf("[DEBUG] Map dimensions - Height: %d, Width: %d\n", map->height, map->width);

>>>>>>> 65ac913c6d78f2c2c50a27b7732a73cd95b0ef02
}
