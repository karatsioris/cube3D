/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piotrwojnarowski <piotrwojnarowski@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 09:53:32 by piotrwojnar       #+#    #+#             */
/*   Updated: 2025/01/06 20:36:54 by piotrwojnar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	validate_line(char *line)
{
	char	*trimmed;

	if (!line)
		return (0);
	trimmed = ft_strtrim(line, " \n\t");
	if (!trimmed || *trimmed == '\0')
	{
		free(trimmed);
		return (0);
	}
	free(trimmed);
	return (1);
}

void	print_list1(t_list *list)
{
	int	i;

	i = 0;
	if (!list)
	{
		printf("[ERROR] Linked list is NULL.\n");
		return ;
	}
	while (list)
	{
		if (list->line)
			printf("[DEBUG] List Node %d: '%s'\n", i, list->line);
		else
			printf("[ERROR] List Node %d: (NULL line)\n", i);
		list = list->next;
		i++;
	}
}

int	put_on_list(char *line, t_list **list, t_memory *mem)
{
	t_list	*node;

	if (!line || *line == '\0' || *line == '\n')
	{
		printf("[ERROR] Cannot add an empty or NULL line to the list.\n");
		return (0);
	}
	node = mem_alloc(mem, sizeof(t_list));
	if (!node)
	{
		printf("[ERROR] Failed to allocate memory for map list node.\n");
		return (0);
	}
	node->line = ft_strdup_cub(line, mem);
	if (!node->line || node->line[0] == '\0')
	{
		printf("[ERROR] Failed to duplicate map line content.\n");
		return (0);
	}
	node->next = NULL;
	if (!(*list))
	{
		*list = node;
		printf("[DEBUG] Added first node to map list: '%s'\n", node->line);
	}
	else
	{
		t_list *temp = *list;
		while (temp->next)
			temp = temp->next;
		temp->next = node;
		printf("[DEBUG] Added node to map list: '%s'\n", node->line);
	}
	printf("[DEBUG] Current state of the linked list:\n");
	print_list1(*list);
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
