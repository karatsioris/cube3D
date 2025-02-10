/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 09:39:53 by piotrwojnar       #+#    #+#             */
/*   Updated: 2025/02/10 15:03:52 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	is_valid_color_component(char *str)
{
	if (!str || *str == '\0')
		return (false);
	while (*str)
	{
		if (!ft_isdigit((unsigned char)*str))
			return (false);
		str++;
	}
	return (true);
}

static char	*extract_trimmed_line_after_directive(char *line)
{
	while (*line && *line != ' ')
		line++;
	while (*line == ' ')
		line++;
	return (ft_strtrim(line, " \t\n"));
}

static int	parse_component(char *str)
{
	char	*trimmed;
	int		value;

	trimmed = ft_strtrim(str, " \t\n");
	if (!trimmed || !is_valid_color_component(trimmed))
	{
		if (trimmed)
			free(trimmed);
		ft_error(-7);
	}
	value = ft_atoi(trimmed);
	validate_color_range(value);
	free(trimmed);
	return (value);
}

void	parse_color(char *line, int color[3])
{
	char	**rgb;
	char	*trimmed_line;
	int		idx;

	if (color[0] != -1)
		ft_error(-8);
	trimmed_line = extract_trimmed_line_after_directive(line);
	if (!trimmed_line)
		ft_error(-7);
	rgb = ft_split(trimmed_line, ',');
	free(trimmed_line);
	if (!rgb || ft_arraylen(rgb) != 3)
		ft_error(-7);
	idx = 0;
	while (idx < 3)
	{
		color[idx] = parse_component(rgb[idx]);
		idx++;
	}
	ft_free_split(rgb);
}
