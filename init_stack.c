/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_stack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-tole <ade-tole@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 21:45:25 by ade-tole          #+#    #+#             */
/*   Updated: 2023/11/26 22:35:30 by ade-tole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

long	ft_atol(char *str)
{
	long	nbr;
	int		sign;

	nbr = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -sign;
		str++;
	}
	while (*str > 47 && *str < 58)
	{
		nbr = nbr * 10 + (*str - 48);
		str++;
	}
	return (sign * nbr);
}

t_node	*init_stack(t_node **head, char **argv)
{
	t_node	*new_node;
	t_node	*prev_node;
	int		i;

	i = 1;
	while (argv[i])
	{
		new_node = (t_node *)malloc(sizeof(t_node));
		if (!new_node)
			return (0);
		new_node->data = (int)ft_atol(argv[i]);
		new_node->next = NULL;
		if (!*head)
		{
			*head = new_node;
			new_node->prev = NULL;
		}
		else
		{
			prev_node->next = new_node;
			new_node->prev = prev_node;
		}
		prev_node = new_node;
		i++;
	}
	return (*head);
}
