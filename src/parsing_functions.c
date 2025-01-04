/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piotrwojnarowski <piotrwojnarowski@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 10:58:00 by piotrwojnar       #+#    #+#             */
/*   Updated: 2025/01/04 12:58:44 by piotrwojnar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

bool	is_map_line(char *line)
{
	while (*line)
	{
		if (*line != '1' && *line != '0' && *line != 'N' && *line != 'S'
			&& *line != 'E' && *line != 'W' && *line != ' ' && *line != '\n')
			return (false);
		line++;
	}
	return (true);
}
void	parse_line(char *line, t_config *config,
			t_memory *mem, bool *is_parsing_map)
{
	ft_printf("\n[DEBUG] ----- Parsing Line -----\n");
	ft_printf("[DEBUG] Received line: '%s'\n", line);
	ft_printf("[DEBUG] Parsing state: %s\n",
		*is_parsing_map ? "Parsing Map" : "Parsing Config");

	if (*is_parsing_map)
	{
		ft_printf("[DEBUG] State: Parsing Map Section\n");
		if (is_map_line(line))
		{
			ft_printf("[DEBUG] Valid map line detected. Processing map line...\n");
			process_line(&config->map, mem, ft_strdup(line));
		}
		else if (*line == '\n' || *line == '\0')
		{
			ft_printf("[DEBUG] Empty map line detected. Skipping...\n");
			return ;
		}
		else
		{
			ft_printf("[ERROR] Invalid line in map section: '%s'\n", line);
			ft_error(-9);
		}
		return ;
	}
	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0 ||
		ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0)
	{
		ft_printf("[DEBUG] Texture directive detected: '%s'\n", line);
		parse_texture(line, &config->textures);
		return ;
	}

	else if (line[0] == 'F' || line[0] == 'C')
	{
		ft_printf("[DEBUG] Color directive detected: '%s'\n", line);
		parse_color(line, (line[0] == 'F') ? config->colors.floor : config->colors.ceiling);
		return ;
	}
	else if (is_map_line(line))
	{
		ft_printf("[DEBUG] Start of map grid detected.\n");
		*is_parsing_map = true;
		process_line(&config->map, mem, ft_strdup(line));
	}
}

void	parse_cub_file(t_config *config, t_memory *mem, char *file_path)
{
	int		fd;
	char	*line;
	bool	is_parsing_map = false;

	ft_printf("[DEBUG] Validating file extension: %s\n", file_path);
	if (!has_valid_extension(file_path, ".cub"))
	{
		ft_printf("[ERROR] Invalid map file extension. Expected '.cub'\n");
		exit(1);
	}

	ft_printf("[DEBUG] Opening map file: %s\n", file_path);
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("[ERROR] Failed to open map file: %s\n", file_path);
		exit(1);
	}
	config->map.path = mem_alloc(mem, ft_strlen(file_path) + 1);
	ft_strlcpy(config->map.path, file_path, ft_strlen(file_path) + 1);

	config->map.current_row = 0;
	config->map.height = 0;
	config->map.width = 0;
	config->map.list = NULL;
	while ((line = get_next_line(fd)))
	{
		ft_printf("[DEBUG] Parsing line: %s\n", line);
		parse_line(line, config, mem, &is_parsing_map);
		free(line);
	}
	close(fd);
	if (!config->map.list)
	{
		ft_printf("[ERROR] Map list was not populated!\n");
		exit(1);
	}
	ft_printf("[DEBUG] Converting map list to grid...\n");
	list_to_array(&config->map, mem);
	ft_printf("[DEBUG] Calculating map dimensions...\n");
	config->map.height = 0;
	while (config->map.grid[config->map.height])
		config->map.height++;
	config->map.width = (config->map.height > 0) ? ft_strlen(config->map.grid[0]) : 0;
	ft_printf("[DEBUG] Map dimensions: Height=%d, Width=%d\n",
		config->map.height, config->map.width);
	ft_printf("[DEBUG] Validating textures and colors...\n");
	validate_textures_and_colors(config);
	ft_printf("[DEBUG] Validating map boundaries...\n");
	validate_map_boundary(&config->map);
	ft_printf("[DEBUG] Map successfully parsed and validated!\n");
}
