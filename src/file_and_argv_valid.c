/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_and_argv_valid.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piotrwojnarowski <piotrwojnarowski@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 09:32:54 by piotrwojnar       #+#    #+#             */
/*   Updated: 2025/01/06 22:05:31 by piotrwojnar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

bool	validate_args_and_load_map(int argc,
			char **argv, t_config *config, t_memory *mem)
{
	ft_printf("[DEBUG] Validating command-line arguments...\n");
	if (argc < 2)
	{
		ft_printf("[ERROR] Missing map path argument!\n");
		return (false);
	}
	else if (argc > 2)
	{
		ft_printf("[ERROR] Too many arguments! Received %d arguments.\n", argc);
		return (false);
	}
	ft_printf("[DEBUG] Parsing map file: %s\n", argv[1]);
	parse_cub_file(config, mem, argv[1]);
	ft_printf("[DEBUG] Map parsed and loaded successfully.\n");
	return (true);
}

int	has_valid_extension(const char *path, const char *extension)
{
	int			path_len;
	int			ext_len;
	const char	*path_ext;

	path_len = ft_strlen(path);
	ext_len = ft_strlen(extension);
	if (path_len < ext_len)
		return (0);
	path_ext = path + path_len - ext_len;
	while (*extension)
	{
		if (*path_ext != *extension)
			return (0);
		path_ext++;
		extension++;
	}
	return (1);
}
