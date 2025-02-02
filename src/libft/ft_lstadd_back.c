/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piotrwojnarowski <piotrwojnarowski@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 15:18:16 by pwojnaro          #+#    #+#             */
/*   Updated: 2025/01/06 14:49:06 by piotrwojnar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;
	int		safety_counter = 1000000; // Arbitrary large number for safety

	if (!lst || !new)
	{
		ft_printf("[ERROR] Invalid input to ft_lstadd_back.\n");
		return ;
	}
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next)
	{
		if (--safety_counter <= 0)
		{
			ft_printf("[ERROR] Infinite loop detected in ft_lstadd_back.\n");
			return ;
		}
		temp = temp->next;
	}
	temp->next = new;
	ft_printf("[DEBUG] Node added to the end of the list.\n");
}
