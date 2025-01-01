/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piotrwojnarowski <piotrwojnarowski@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 12:23:56 by piotrwojnar       #+#    #+#             */
/*   Updated: 2025/01/01 12:39:34 by piotrwojnar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "cub3d.h"

// int	main(int argc, char **argv)
// {
// 	t_config	config;

// 	if (argc != 2)
// 		ft_error(-12);

// 	ft_memset(&config, 0, sizeof(t_config));
// 	config.colors.floor[0] = -1;
// 	config.colors.ceiling[0] = -1;

// 	parse_cub_file(&config, argv[1]);
// 	validate_textures_and_colors(&config);

// 	ft_printf("Textures and Colors Parsed Successfully!\n");

// 	return (0);
// }
#include <stdio.h>

int main(void)
{
    printf("Hello from cub3D!\n");
    return 0;
}
