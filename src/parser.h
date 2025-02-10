/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 16:31:29 by pwojnaro          #+#    #+#             */
/*   Updated: 2025/02/10 14:38:19 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdbool.h>
# include "cube3d.h"

void	parse_texture(char *line, t_texture *textures, t_memory *mem);
void	parse_color(char *line, int color[3]);
bool	validate_args_and_load_map(int argc, char **argv, t_config *config,
			t_memory *mem);
void	parse_line(char *line, t_config *config, t_memory *mem,
			bool *is_parsing_map);
void	parse_cub_file(t_config *config, t_memory *mem, char *file_path);
void	list_to_array(t_map *map, t_memory *mem);
int		put_on_list(const char *line, t_list **list, t_memory *mem);
int		has_valid_extension(const char *path, const char *extension);
char	*ft_strdup_cub(const char *src, t_memory *mem);
void	validate_color_range(int color);
void	validate_config(t_config *config);

#endif
