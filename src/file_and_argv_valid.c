/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_and_argv_valid.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piotrwojnarowski <piotrwojnarowski@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 09:32:54 by piotrwojnar       #+#    #+#             */
/*   Updated: 2025/01/01 09:54:44 by piotrwojnar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	validate_args_and_load_map(int argc, char **argv, t_map *map)
{
	if (argc < 2)
	{
		ft_printf("Missing map path argument!\n");
		exit(1);
	}
	else if (argc > 2)
	{
		ft_printf("Too many arguments!\n");
		exit(1);
	}
	*map = (t_map){0};
	if (load_map(map, argv[1]) != 0)
	{
		exit(1);
	}
}

int	has_valid_extension(const char *path, const char *extension)
{
	int			path_len;
	int			ext_len;
	const char	*path_ext;

	path_len = ft_strlen(path);
	ext_len = ft_strlen(extension);
	if (path_len < ext_len)
		return (0);
	path_ext = path + path_len - ext_len;
	while (*extension)
	{
		if (*path_ext != *extension)
			return (0);
		path_ext++;
		extension++;
	}
	return (1);
}

void	validate_file_extension(t_map *map)
{
	if (!has_valid_extension(map->path, ".cub"))
	{
		ft_printf("Error: The map file must end with *.cub!\n");
		exit(1);
	}
	map->fd = open(map->path, O_RDONLY);
}
