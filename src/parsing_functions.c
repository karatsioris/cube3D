/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piotrwojnarowski <piotrwojnarowski@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 10:58:00 by piotrwojnar       #+#    #+#             */
/*   Updated: 2025/01/06 21:48:17 by piotrwojnar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

bool	is_map_line(char *line)
{
	while (*line)
	{
		if (*line != '1' && *line != '0' && *line != 'N' && *line != 'S' &&
			*line != 'E' && *line != 'W' && *line != ' ' && *line != '\n')
			return (false);
		line++;
	}
	return (true);
}

void	parse_line(char *line, t_config *config, t_memory *mem,
	bool *is_parsing_map)
{
	ft_printf("\n[DEBUG] ----- Parsing Line -----\n");
	ft_printf("[DEBUG] Received line: '%s'\n", line);
	ft_printf("[DEBUG] Parsing state: %s\n", *is_parsing_map ? "Parsing Map"
		: "Parsing Config");
	while (*line == ' ' || *line == '\t')
		line++;
	if (*line == '\0' || *line == '\n')
	{
		ft_printf("[DEBUG] Empty line detected. Skipping...\n");
		return ;
	}
	if (*is_parsing_map)
	{
		if (is_map_line(line))
		{
			ft_printf("[DEBUG] Valid map line detected. Processing...\n");
			if (!put_on_list(line, &config->map.list, mem))
			{
				ft_printf("[ERROR] Failed to add map line to the list.\n");
				exit(1);
			}
		}
		else
		{
			ft_printf("[ERROR] Invalid line in map section: '%s'\n", line);
			exit(1);
		}
		return ;
	}
	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0 ||
		ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0)
	{
		ft_printf("[DEBUG] Texture directive detected.\n");
		parse_texture(line, &config->textures, mem);
		return ;
	}
	else if (line[0] == 'F' || line[0] == 'C')
	{
		ft_printf("[DEBUG] Color directive detected.\n");
		parse_color(line, (line[0] == 'F') ? config->colors.floor
			: config->colors.ceiling);
		return ;
	}
	else if (is_map_line(line))
	{
		ft_printf("[DEBUG] Map section detected. Switching to Parsing Map state.\n");
		*is_parsing_map = true;
		if (!put_on_list(line, &config->map.list, mem))
		{
			ft_printf("[ERROR] Failed to add map line to the list.\n");
			exit(1);
		}
	}
	else
	{
		ft_printf("[ERROR] Unknown configuration directive: '%s'\n", line);
		exit(1);
	}
}

void	parse_cub_file(t_config *config, t_memory *mem, char *file_path)
{
	int		fd;
	char	*line;
	bool	is_parsing_map;

	is_parsing_map = false;
	ft_printf("[DEBUG] Validating file extension: %s\n", file_path);
	if (!has_valid_extension(file_path, ".cub"))
		ft_error(-1);
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
		ft_error(-13);
	ft_printf("[DEBUG] Converting map list to grid...\n");
	list_to_array(&config->map, mem);
	ft_printf("[DEBUG] Validating textures and colors...\n");
	validate_textures_and_colors(config);
	ft_printf("[DEBUG] Validating map boundaries...\n");
	validate_map_boundary(&config->map);
	ft_printf("[DEBUG] Map successfully parsed and validated!\n");
}
