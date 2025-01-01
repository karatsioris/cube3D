/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piotrwojnarowski <piotrwojnarowski@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 10:54:18 by piotrwojnar       #+#    #+#             */
/*   Updated: 2025/01/01 15:39:18 by piotrwojnar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

char	*extract_path(char *line)
{
	char	*path;

	while (*line && *line != ' ')
		line++;
	while (*line && *line == ' ')
		line++;
	path = ft_strdup(line);
	if (!path || open(path, O_RDONLY) < 0)
	{
		ft_error(-6);
	}
	close(open(path, O_RDONLY));

	return (path);
}

void	parse_texture(char *line, t_texture *textures)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		textures->north = extract_path(line);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		textures->south = extract_path(line);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		textures->west = extract_path(line);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		textures->east = extract_path(line);
	else
		ft_error(-6);
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
	if (!config->textures.north || !config->textures.south
		|| !config->textures.west || !config->textures.east)
		ft_error(-10);

	if (config->colors.floor[0] == -1 || config->colors.ceiling[0] == -1)
		ft_error(-11);
}
