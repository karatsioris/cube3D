/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 19:50:01 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/03/21 16:13:22 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*concatenated;
	size_t	s1_len;
	size_t	s2_len;
	char	*str_ptr;

	str_ptr = 0;
	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	concatenated = (char *)malloc(1 * (s1_len + s2_len + 1));
	if (!concatenated)
		return (NULL);
	str_ptr = concatenated;
	while (*s1)
		*str_ptr++ = *s1++;
	while (*s2)
		*str_ptr++ = *s2++;
	*str_ptr = '\0';
	return (concatenated);
}
