/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piotrwojnarowski <piotrwojnarowski@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 10:58:00 by piotrwojnar       #+#    #+#             */
/*   Updated: 2025/01/01 10:58:25 by piotrwojnar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cube3d.h"

void	parse_line(char *line, t_config *config)
{
	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0 ||
		ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0)
		parse_texture(line, &config->textures);
	else if (line[0] == 'F')
		parse_color(line, config->colors.floor);
	else if (line[0] == 'C')
		parse_color(line, config->colors.ceiling);
	else if (*line == '1' || *line == '0' || *line == ' ')
		process_line(&config->map, ft_strdup(line));
	else if (*line == '\n' || *line == '\0')
		return; // Ignore empty lines
	else
		ft_error(-9); // Error: Invalid map configuration line
}
void	parse_cub_file(t_config *config, char *file_path)
{
	int		fd;
	char	*line;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		ft_error(-1); // Error: Cannot open file

	while ((line = get_next_line(fd)))
	{
		parse_line(line, config);
		free(line);
	}
	close(fd);
}
