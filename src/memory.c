/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piotrwojnarowski <piotrwojnarowski@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 20:34:56 by piotrwojnar       #+#    #+#             */
/*   Updated: 2025/01/06 12:51:21 by piotrwojnar      ###   ########.fr       */
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
	mem->allocated_pointers = calloc(mem->capacity, sizeof(void *));
	if (!mem->allocated_pointers)
	{
		ft_printf("[ERROR] Failed to allocate memory for pointer array.\n");
		return (false);
	}
	ft_printf("[DEBUG] Memory manager initialized with capacity: %lu\n",
		(unsigned long)mem->capacity);
	return (true);
}

void	*mem_alloc(t_memory *mem, size_t size)
{
	void	*ptr;
	size_t	new_capacity;

	if (!mem || !mem->allocated_pointers)
	{
		ft_printf("[ERROR] mem_alloc received an invalid memory manager.\n");
		return (NULL);
	}
	if (mem->count >= mem->capacity)
	{
		new_capacity = mem->capacity * 2;
		void **new_alloc = realloc(mem->allocated_pointers,
				sizeof(void *) * new_capacity);
		if (!new_alloc)
		{
			ft_printf("[ERROR] Failed to expand memory manager capacity.\n");
			return (NULL);
		}
		mem->allocated_pointers = new_alloc;
		mem->capacity = new_capacity;
		ft_printf("[DEBUG] Memory manager capacity increased to: %lu\n",
			(unsigned long)mem->capacity);
	}
	ptr = malloc(size);
	if (!ptr)
	{
		ft_printf("[ERROR] Failed to allocate %lu bytes.\n",
			(unsigned long)size);
		return (NULL);
	}
	mem->allocated_pointers[mem->count++] = ptr;
	ft_printf("[DEBUG] Allocated %lu bytes. Total allocations: %lu\n",
		(unsigned long)size, (unsigned long)mem->count);
	return (ptr);
}

void	mem_free_all(t_memory *mem)
{
	if (!mem || !mem->allocated_pointers)
	{
		ft_printf("Mem_free_all received an uninitialized memory manager.\n");
		return ;
	}
	ft_printf("[DEBUG] Freeing %zu allocations...\n", mem->count);
	for (size_t i = 0; i < mem->count; i++)
	{
		if (mem->allocated_pointers[i])
		{
			free(mem->allocated_pointers[i]);
			mem->allocated_pointers[i] = NULL;
		}
	}
	free(mem->allocated_pointers);
	mem->allocated_pointers = NULL;
	mem->count = 0;
	mem->capacity = 0;
	ft_printf("[DEBUG] All memory allocations have been freed.\n");
}

char	*ft_strdup_cub(const char *src, t_memory *mem)
{
	int		len;
	char	*dest;

	if (!src || !mem)
	{
		ft_printf("[ERROR] Invalid arguments passed to ft_strdup_cub.\n");
		return (NULL);
	}
	len = ft_strlen(src);
	dest = (char *)mem_alloc(mem, sizeof(char) * (len + 1));
	if (!dest)
	{
		ft_printf("[ERROR] Failed to allocate memory in ft_strdup_cub.\n");
		return (NULL);
	}
	ft_strlcpy(dest, src, len + 1);
	ft_printf("Ft_strdup_cub allocated %d bytes and in memory.\n", len + 1);
	return (dest);
}
