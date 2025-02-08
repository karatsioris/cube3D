/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 10:54:18 by piotrwojnar       #+#    #+#             */
/*   Updated: 2025/02/08 16:18:09 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*clean_path(char *line, t_memory *mem)
{
	char	*raw_path;
	int		len;

	ft_printf("[DEBUG] Extracting path from line: '%s'\n", line);
	while (*line != ' ')
		line++;
	while (*line == ' ')
		line++;
	if (!*line)
		return (NULL);
	raw_path = ft_strdup_cub(line, mem);
	if (!raw_path)
		ft_error(-12);
	len = ft_strlen(raw_path);
	while (len > 0 && (raw_path[len - 1] == ' ' || raw_path[len - 1] == '\n'
			|| raw_path[len - 1] == '\t'))
	{
		raw_path[len - 1] = '\0';
		len--;
	}
	ft_printf("[DEBUG] Cleaned path: '%s'\n", raw_path);
	return (raw_path);
}

int	validate_path(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		free(path);
		return (0);
	}
	close(fd);
	return (1);
}

char	*extract_path(char *line, t_memory *mem)
{
	char	*path;

	path = clean_path(line, mem);
	if (!path || !validate_path(path))
		exit(1);
	return (path);
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
		ft_error(-9);
}
