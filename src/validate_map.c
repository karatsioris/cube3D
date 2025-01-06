/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piotrwojnarowski <piotrwojnarowski@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 09:53:32 by piotrwojnar       #+#    #+#             */
/*   Updated: 2025/01/06 16:35:32 by piotrwojnar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	put_on_list(char *line, t_list **list, t_memory *mem)
{
	t_list	*node;
	t_list	*temp;

	if (!line || *line == '\0' || *line == '\n')
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
	node->line = ft_strdup_cub(line, mem);
	if (!node->line || node->line[0] == '\0')
	{
		ft_printf("[ERROR] Failed to duplicate map line content.\n");
		return (0);
	}
	node->next = NULL;
	if (!(*list))
		*list = node;
	else
	{
		temp = *list;
		while (temp->next)
			temp = temp->next;
		temp->next = node;
	}
	ft_printf("[DEBUG] Added line to map list: '%s'\n", node->line);
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
	if (!put_on_list(line, &map->list, mem))
	{
		ft_printf("[ERROR] Failed to add map line to list.\n");
		exit(1);
	}
}
