/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 12:23:56 by piotrwojnar       #+#    #+#             */
/*   Updated: 2025/02/10 14:16:30 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	system_leaks(void)
{
	system("leaks cub3D");
}

void	check_leaks(void)
{
	atexit(system_leaks);
}

int	main(int argc, char **argv)
{
	t_config	config;
	t_memory	mem;

	if (!init_config_and_map(&config, &mem, argc, argv))
		return (1);
	game_loop(&config.map, &config);
	ft_clean(&config.map, &mem, &config.resources);
	return (0);
}
