/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 10:58:00 by piotrwojnar       #+#    #+#             */
/*   Updated: 2025/02/04 17:08:25 by pwojnaro         ###   ########.fr       */
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

void	handle_map_line(char *line, t_config *config, t_memory *mem)
{
	int	i;

	if (!put_on_list(line, &config->map.list, mem))
		exit(1);
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E'
			|| line[i] == 'W')
		{
			config->player.x = config->map.current_row + 1;
			config->player.y = i;
		}
		i++;
	}
	config->map.current_row++;
}

void	handle_config_line(char *line, t_config *config, t_memory *mem)
{
	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0)
	{
		parse_texture(line, &config->textures, mem);
	}
	else if (line[0] == 'F')
	{
		parse_color(line, config->colors.floor);
	}
	else if (line[0] == 'C')
	{
		parse_color(line, config->colors.ceiling);
	}
	else
	{
		exit(1);
	}
}

void	parse_line(char *line, t_config *config, t_memory *mem,
		bool *is_parsing_map)
{
	while (*line == ' ' || *line == '\t')
		line++;
	if (*line == '\0' || *line == '\n')
		return ;
	if (*is_parsing_map)
	{
		if (is_map_line(line))
			handle_map_line(line, config, mem);
		else
			exit(1);
		return ;
	}
	if (is_map_line(line))
	{
		*is_parsing_map = true;
		handle_map_line(line, config, mem);
	}
	else
	{
		handle_config_line(line, config, mem);
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
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		exit(1);
	config->map.path = mem_alloc(mem, ft_strlen(file_path) + 1);
	ft_strlcpy(config->map.path, file_path, ft_strlen(file_path) + 1);
	line = get_next_line(fd);
	while (line)
	{
		parse_line(line, config, mem, &is_parsing_map);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (!config->map.list)
		ft_error(-13);
	list_to_array(&config->map, mem);
}
