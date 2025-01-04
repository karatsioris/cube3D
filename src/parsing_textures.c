/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piotrwojnarowski <piotrwojnarowski@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 10:54:18 by piotrwojnar       #+#    #+#             */
/*   Updated: 2025/01/04 12:56:22 by piotrwojnar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

char	*extract_path(char *line)
{
	char	*raw_path;
	int		len;
	int		fd;

	ft_printf("[DEBUG] Extracting path from line: '%s'\n", line);

	while (*line && *line != ' ')
		line++;
	while (*line && *line == ' ')
		line++;
	raw_path = ft_strdup(line);
	if (!raw_path)
	{
		ft_printf("[ERROR] Memory allocation failed while extracting path.\n");
		ft_error(-6);
	}
	len = ft_strlen(raw_path);
	while (len > 0 && (raw_path[len - 1] == ' ' || raw_path[len - 1] == '\n'
			|| raw_path[len - 1] == '\t'))
	{
		raw_path[len - 1] = '\0';
		len--;
	}
	ft_printf("[DEBUG] Cleaned path: '%s'\n", raw_path);
	fd = open(raw_path, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("[ERROR] Failed to open file: '%s' (errno: %d, %s)\n",
			raw_path, errno, strerror(errno));
		free(raw_path);
		ft_error(-6);
	}
	close(fd);

	ft_printf("[DEBUG] Successfully validated texture path: '%s'\n", raw_path);
	return raw_path;
}

void	parse_texture(char *line, t_texture *textures)
{
	char	*path;

	ft_printf("[DEBUG] Entering parse_texture with line: '%s'\n", line);
	path = extract_path(line);
	if (!path)
	{
		ft_printf("[ERROR] Failed to extract path from texture: '%s'\n", line);
		ft_error(-6);
	}

	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		ft_printf("[DEBUG] Setting North texture: %s\n", path);
		textures->north = path;
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		ft_printf("[DEBUG] Setting South texture: %s\n", path);
		textures->south = path;
	}
	else if (ft_strncmp(line, "WE ", 3) == 0)
	{
		ft_printf("[DEBUG] Setting West texture: %s\n", path);
		textures->west = path;
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		ft_printf("[DEBUG] Setting East texture: %s\n", path);
		textures->east = path;
	}
	else
	{
		ft_printf("[ERROR] Unknown texture directive: '%s'\n", line);
		free(path);
		ft_error(-6);
	}
	ft_printf("[DEBUG] Texture parsed successfully: %s\n", path);
}

void	validate_color_range(int color)
{
	if (color < 0 || color > 255)
		ft_error(-7);
}

void	parse_color(char *line, int color[3])
{
	char	**rgb;
	int		i;

	while (*line && *line != ' ')
		line++;
	while (*line && *line == ' ')
		line++;
	rgb = ft_split(line, ',');
	if (!rgb || ft_arraylen(rgb) != 3)
		ft_error(-8);
	i = 0;
	while (i < 3)
	{
		color[i] = ft_atoi(rgb[i]);
		validate_color_range(color[i]);
		i++;
	}
	ft_free_split(rgb);
}

void	validate_textures_and_colors(t_config *config)
{
	ft_printf("[DEBUG] Validating textures and colors...\n");

	if (!config->textures.north || !config->textures.south
		|| !config->textures.west || !config->textures.east)
	{
		ft_printf("[ERROR] Missing texture path! North: %s, South: %s, West: %s, East: %s\n",
			config->textures.north ? config->textures.north : "NULL",
			config->textures.south ? config->textures.south : "NULL",
			config->textures.west ? config->textures.west : "NULL",
			config->textures.east ? config->textures.east : "NULL");
		ft_error(-10);
	}

	if (config->colors.floor[0] == -1 || config->colors.ceiling[0] == -1)
	{
		ft_printf("[ERROR] Missing floor or ceiling color! Floor: %d,%d,%d, Ceiling: %d,%d,%d\n",
			config->colors.floor[0], config->colors.floor[1], config->colors.floor[2],
			config->colors.ceiling[0], config->colors.ceiling[1], config->colors.ceiling[2]);
		ft_error(-11);
	}
	ft_printf("[DEBUG] Textures and colors validated successfully.\n");
}

