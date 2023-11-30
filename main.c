/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-tole <ade-tole@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 19:29:16 by ade-tole          #+#    #+#             */
/*   Updated: 2023/11/28 15:26:09 by ade-tole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// test print list
#include <stdio.h>
void	print_stack(t_node **head)
{
	t_node	*current = *head;

	while (current)
	{
		printf("%d ", current->data);
		current = current->next;
	}
	printf("\n");
}


int	main(int argc, char **argv)
{
	t_node	*stack_a;
	t_node	*stack_b;

	if (argc == 1)
	{
		write(2, "Error\n", 6);
		exit (1);
	}
	stack_a = init_stack(&stack_a, argv);
	print_stack(&stack_a);
	print_stack(&stack_b);
	push_swap(&stack_a, &stack_b);
	print_stack(&stack_a);
	return (0);
}	
