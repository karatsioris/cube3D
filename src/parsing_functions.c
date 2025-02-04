/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 10:58:00 by piotrwojnar       #+#    #+#             */
/*   Updated: 2025/02/04 14:07:56 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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

void	parse_line(char *line, t_config *config, t_memory *mem,
	bool *is_parsing_map)
{
	ft_printf("\n[DEBUG] ----- Parsing Line -----\n");
	ft_printf("[DEBUG] Received line: '%s'\n", line);
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
			for (int i = 0; line[i] != '\0'; i++)
			{
				if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
				{
					config->player.x = config->map.current_row + 1;
					config->player.y = i;
				}
			}
			config->map.current_row++;
		}
		else
		{
			ft_printf("[ERROR] Invalid line in map section: '%s'\n", line);
			exit(1);
		}
		return ;
	}
	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0)
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
		ft_printf("[DEBUG] Switching to Parsing Map state.\n");
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
	ft_printf("[DEBUG] Map parsing completed.\n");
}
