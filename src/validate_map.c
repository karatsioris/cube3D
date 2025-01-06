/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piotrwojnarowski <piotrwojnarowski@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 09:53:32 by piotrwojnar       #+#    #+#             */
/*   Updated: 2025/01/06 13:42:31 by piotrwojnar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	put_on_list(char *line, t_map *map, t_memory *mem)
{
	t_list	*node;

	if (!line || *line == '\0')
	{
		ft_printf("[ERROR] Cannot add an empty or NULL line to the list.\n");
		return (0);
	}
	node = mem_alloc(mem, sizeof(t_list));
	if (!node)
	{
		ft_printf("[ERROR] Failed to allocate memory for map list node.\n");
		return (0);
	}
	node->content = ft_strdup(line);
	node->next = NULL;
	if (!node->content)
	{
		ft_printf("[ERROR] Failed to duplicate map line content.\n");
		return (0);
	}
	ft_lstadd_back(&map->list, node);
	return (1);
}

void	process_line(t_map *map, t_memory *mem, char *line)
{
	if (!line || *line == '\0' || *line == '\n')
	{
		ft_printf("[DEBUG] Skipping invalid or empty map line.\n");
		return ;
	}
	ft_printf("[DEBUG] Adding map line to list: %s\n", line);
	if (!put_on_list(line, map, mem))
	{
		ft_printf("[ERROR] Failed to add map line to list.\n");
		exit(1);
	}
}
