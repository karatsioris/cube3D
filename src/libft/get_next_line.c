/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:10:01 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/09/15 12:39:57 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*read_and_store(int fd, int *bytes_read, char *line)
{
	char	*storage;

	if (!line)
	{
		line = ft_calloc(1, sizeof(char));
		if (!line)
			return (NULL);
	}
	storage = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!storage)
		return (free(line), NULL);
	while (*bytes_read > 0)
	{
		if (read_from_fd(fd, storage, bytes_read) == -1)
			return (free(storage), free(line), NULL);
		line = store_and_join(line, storage);
		if (!line)
			return (free(storage), NULL);
		if (ft_strchr(storage, '\n'))
			break ;
	}
	free(storage);
	return (line);
}

int	end_of_line(const char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\n' && line[i])
		i++;
	return (i);
}

char	*get_result(const char *line, int bytes_read)
{
	char	*res;
	int		i;

	i = 0;
	if (!line[i])
		return (NULL);
	res = ft_calloc(bytes_read + 2, sizeof(char));
	if (!res)
		return (NULL);
	while (line[i] != '\n' && line[i] != '\0')
	{
		res[i] = line[i];
		i++;
	}
	if (line[i] == '\n')
		res[i] = '\n';
	return (res);
}

char	*new_line(char *line, int bytes)
{
	char	*new;
	int		i;

	i = 0;
	if (!line || !line[bytes])
	{
		free(line);
		return (NULL);
	}
	new = ft_calloc(ft_strlen(line) - bytes + 1, sizeof(char));
	if (!new)
		return (free(line), NULL);
	bytes ++;
	while (line[bytes])
	{
		new[i] = line[bytes];
		i++;
		bytes++;
	}
	free(line);
	return (new);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*res;
	int			bytes;

	bytes = 1;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (line)
		{
			free(line);
			line = NULL;
		}
		return (NULL);
	}
	line = read_and_store(fd, &bytes, line);
	if (!line)
		return (NULL);
	bytes = end_of_line(line);
	res = get_result(line, bytes);
	line = new_line(line, bytes);
	return (res);
}
