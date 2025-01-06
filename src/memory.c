/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piotrwojnarowski <piotrwojnarowski@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 20:34:56 by piotrwojnar       #+#    #+#             */
/*   Updated: 2025/01/06 21:53:00 by piotrwojnar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

bool	mem_init(t_memory *mem)
{
	if (!mem)
	{
		printf("[ERROR] mem_init received a NULL pointer.\n");
		return (false);
	}
	mem->capacity = INITIAL_MEM_CAPACITY;
	mem->count = 0;
	mem->allocated_pointers = calloc(mem->capacity, sizeof(void *));
	if (!mem->allocated_pointers)
	{
		printf("[ERROR] Failed to allocate memory for pointer array.\n");
		return (false);
	}
	printf("[DEBUG] Memory manager initialized with capacity: %zu\n",
		mem->capacity);
	return (true);
}

void	*mem_alloc(t_memory *mem, size_t size)
{
	void	*ptr;

	if (!mem || !mem->allocated_pointers)
	{
		printf("[ERROR] Invalid memory manager.\n");
		exit(1);
	}
	if (mem->count >= mem->capacity)
	{
		mem->capacity *= 2;
		mem->allocated_pointers = realloc(mem->allocated_pointers,
				sizeof(void *) * mem->capacity);
		if (!mem->allocated_pointers)
		{
			printf("[ERROR] Failed to expand memory capacity.\n");
			exit(1);
		}
		printf("[DEBUG] Memory manager capacity expanded to: %zu\n",
			mem->capacity);
	}
	ptr = malloc(size);
	if (!ptr)
	{
		printf("[ERROR] Failed to allocate %zu bytes.\n", size);
		exit(1);
	}
	mem->allocated_pointers[mem->count++] = ptr;
	printf("[DEBUG] Allocated %zu bytes. Total allocations: %zu\n",
		size, mem->count);
	return (ptr);
}

void	mem_free_all(t_memory *mem)
{
	if (!mem || !mem->allocated_pointers)
	{
		printf("[ERROR] mem_free_all received an uninitialized memory.\n");
		return ;
	}
	printf("[DEBUG] Freeing %zu allocations...\n", mem->count);
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
	printf("[DEBUG] All memory allocations have been freed.\n");
}

char	*ft_strdup_cub(const char *src, t_memory *mem)
{
	char	*dest;
	int		len;

	if (!src || src[0] == '\0')
	{
		printf("[ERROR] ft_strdup_cub received an invalid source string.\n");
		exit(1);
	}
	len = ft_strlen(src);
	dest = (char *)mem_alloc(mem, sizeof(char) * (len + 1));
	if (!dest)
	{
		printf("[ERROR] Failed to allocate memory in ft_strdup_cub.\n");
		exit(1);
	}
	ft_strlcpy(dest, src, len + 1);
	printf("[DEBUG] ft_strdup_cub successfully duplicated string: '%s'\n",
		dest);
	return (dest);
}
