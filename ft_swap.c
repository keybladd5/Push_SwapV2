/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-tole <ade-tole@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 19:32:58 by ade-tole          #+#    #+#             */
/*   Updated: 2023/11/24 13:11:38 by ade-tole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static	void	swap(t_node **head) // 0 1 2 -> 1 0 2
{
	*head = (*head)->next; // head=1
	(*head)->prev->next = (*head)->next; // 0->next=2
	(*head)->prev->prev = *head; // 0->prev=1
	(*head)->next->prev = (*head)->prev; // 2->prev=0
	(*head)->next = (*head)->prev; // 1->next=0
	(*head)->prev = NULL; // 1 first
}

void	sa(t_node **a)
{
	swap(a);
	write(1, "sa\n", 3);
}

void	sb(t_node **b)
{
	swap(b);
	write(1, "sb\n", 3);
}

void	ss(t_node **a, t_node **b)
{
	swap(a);
	swap(b);
	write(1, "ss\n", 3);
}
