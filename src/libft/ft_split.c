/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 17:30:32 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/09/13 14:11:22 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(const char *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			count++;
			while (*s && *s != c)
				s++;
		}
	}
	return (count);
}

void	ft_free_split(char **split)
	{
	int	i;

	i = 0;
	if (!split)
		return ;
	while ((split[i]))
	{
		free(split[i]);
		split[i] = 0;
		i++;
	}
	free(split);
}

static char	*ft_allocate_word(const char *s, size_t start, size_t end)
{
	char	*word;

	if (start >= end)
		return (NULL);
	word = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!word)
		return (NULL);
	ft_strlcpy(word, s + start, end - start + 1);
	return (word);
}

static int	ft_fill_words(char **w, char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	start;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (!s[i])
			break ;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		if (start < i)
		{
			w[j] = ft_allocate_word(s, start, i);
			if (!w[j])
				return (0);
			j++;
		}
	}
	w[j] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**w;
	int		wc;

	if (!s)
		return (NULL);
	wc = ft_count_words(s, c);
	w = malloc(sizeof(char *) * (wc + 1));
	if (!w)
		return (NULL);
	if (!ft_fill_words(w, s, c))
	{
		ft_free_split(w);
		return (NULL);
	}
	return (w);
}
