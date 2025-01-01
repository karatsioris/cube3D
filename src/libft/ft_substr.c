/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:59:21 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/03/16 20:53:05 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	s_length;

	if (!s)
		return (NULL);
	s_length = ft_strlen(s);
	if (start >= s_length)
		len = 0;
	else if (len > s_length - start)
		len = s_length - start;
	substr = (char *)malloc(len + 1);
	if (!substr)
		return (NULL);
	if (len > 0)
		ft_memcpy(substr, s + start, len);
	substr[len] = '\0';
	return (substr);
}
