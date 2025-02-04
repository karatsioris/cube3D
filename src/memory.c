/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 20:34:56 by piotrwojnar       #+#    #+#             */
/*   Updated: 2025/02/04 14:27:36 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

bool	mem_init(t_memory *mem)
{
	if (!mem)
	{
		ft_printf("[ERROR] mem_init received a NULL pointer.\n");
		return (false);
	}
	mem->capacity = INITIAL_MEM_CAPACITY;
	mem->count = 0;
	mem->allocated_pointers = ft_calloc(mem->capacity, sizeof(void *));
	if (!mem->allocated_pointers)
	{
		ft_printf("[ERROR] Failed to allocate memory for pointer array.\n");
		return (false);
	}
	ft_printf("[DEBUG] Memory manager initialized with capacity: %zu\n",
		mem->capacity);
	return (true);
}

void	*mem_alloc(t_memory *mem, size_t size)
{
	void	*ptr;
	size_t	old_capacity;

	if (!mem || !mem->allocated_pointers)
	{
		exit(1);
	}
	if (mem->count >= mem->capacity)
	{
		old_capacity = mem->capacity;
		mem->capacity *= 2;
		mem->allocated_pointers = ft_realloc(mem->allocated_pointers,
				old_capacity * sizeof(void *),
				mem->capacity * sizeof(void *));
		if (!mem->allocated_pointers)
			exit(1);
	}
	ptr = malloc(size);
	if (!ptr)
	{
		ft_printf("[ERROR] Failed to allocate %zu bytes.\n", size);
		exit(1);
	}
	mem->allocated_pointers[mem->count++] = ptr;
	return (ptr);
}

void	mem_free_all(t_memory *mem)
{
	size_t	i;

	i = 0;
	if (!mem || !mem->allocated_pointers)
	{
		ft_printf("[ERROR] mem_free_all received an uninitialized memory.\n");
		return ;
	}
	ft_printf("[DEBUG] Freeing %zu allocations...\n", mem->count);
	while (i < mem->count)
	{
		if (mem->allocated_pointers[i])
		{
			free(mem->allocated_pointers[i]);
			mem->allocated_pointers[i] = NULL;
		}
		i++;
	}
	free(mem->allocated_pointers);
	mem->allocated_pointers = NULL;
	mem->count = 0;
	mem->capacity = 0;
	ft_printf("[DEBUG] All memory allocations have been freed.\n");
}

char	*ft_strdup_cub(const char *src, t_memory *mem)
{
	char	*dest;
	int		len;

	if (!src || src[0] == '\0')
	{
		ft_printf("[ERROR] ft_strdup_cub received an invalid source string.\n");
		exit(1);
	}
	len = ft_strlen(src);
	dest = (char *)mem_alloc(mem, sizeof(char) * (len + 1));
	if (!dest)
	{
		ft_printf("[ERROR] Failed to allocate memory in ft_strdup_cub.\n");
		exit(1);
	}
	ft_strlcpy(dest, src, len + 1);
	ft_printf("[DEBUG] ft_strdup_cub successfully duplicated string: '%s'\n",
		dest);
	return (dest);
}
