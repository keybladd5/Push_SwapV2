/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-tole <ade-tole@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 20:50:31 by ade-tole          #+#    #+#             */
/*   Updated: 2023/11/26 23:30:28 by ade-tole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int		ft_lstsize(t_node *stack)
{
	int	i;

	i = 0;
	if (stack)
	{
		while (stack)
		{
			stack = stack->next;
			i++;
		}
	}
	return (i);
}

t_node	*ft_lstsmallest(t_node *stack)
{
	return (stack);
}

t_node	*lst_findlast(t_node *head)
{
	while (head->next)
		head = head->next;

	return (head);
}
