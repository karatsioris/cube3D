/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 18:49:19 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/09/13 10:32:05 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*store_and_join(char *line, const char *storage)
{
	char	*leftover;

	leftover = ft_strjoin(line, storage);
	if (!leftover)
	{
		free(line);
		return (NULL);
	}
	free(line);
	return (leftover);
}

int	read_from_fd(int fd, char *storage, int *bytes_read)
{
	*bytes_read = read(fd, storage, BUFFER_SIZE);
	if (*bytes_read == -1)
		return (-1);
	storage[*bytes_read] = '\0';
	return (0);
}
