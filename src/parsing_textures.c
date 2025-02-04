/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 10:54:18 by piotrwojnar       #+#    #+#             */
/*   Updated: 2025/02/04 14:06:55 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*extract_path(char *line, t_memory *mem)
{
	char	*raw_path;
	int		len;
	int		fd;

	ft_printf("[DEBUG] Extracting path from line: '%s'\n", line);
	while (*line != ' ')
		line++;
	while (*line == ' ')
		line++;
	if (!*line)
		return (NULL);
	raw_path = ft_strdup_cub(line, mem);
	if (!raw_path)
		exit(1);
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
		free(raw_path);
		exit(1);
	}
	close(fd);
	return (raw_path);
}

void	parse_texture(char *line, t_texture *textures, t_memory *mem)
{
	char	*path;

	ft_printf("[DEBUG] Entering parse_texture with line: '%s'\n", line);
	if (!line || *line == '\0')
		exit(1);
	path = extract_path(line, mem);
	if (!path)
	{
		ft_printf("[ERROR] Failed to extract path from line: '%s'\n", line);
		exit(1);
	}
	if (ft_strncmp(line, "NO ", 3) == 0)
		textures->north = path;
	else if (ft_strncmp(line, "SO ", 3) == 0)
		textures->south = path;
	else if (ft_strncmp(line, "WE ", 3) == 0)
		textures->west = path;
	else if (ft_strncmp(line, "EA ", 3) == 0)
		textures->east = path;
	else
	{
		ft_printf("[ERROR] Unknown texture directive: '%s'\n", line);
		free(path);
		exit(1);
	}
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

	ft_printf("[DEBUG] Parsing color line: '%s'\n", line);
	if (color[0] != -1)
	{
		ft_printf("[ERROR] Duplicate color directive found.\n");
		ft_error(-15);
	}
	while (*line != ' ')
		line++;
	while (*line == ' ')
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
