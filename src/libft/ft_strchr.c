/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:08:45 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/03/14 19:00:55 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(char const *str, int c)
{
	while (*str)
	{
		if (*str == (char)c)
		{
			return ((char *)(str));
		}
		str++;
	}
	if (*str == (char)c)
	{
		return ((char *)str);
	}
	else
		return (0);
}
