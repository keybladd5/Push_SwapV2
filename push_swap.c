/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-tole <ade-tole@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:06:05 by ade-tole          #+#    #+#             */
/*   Updated: 2023/11/28 15:25:26 by ade-tole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static	void	set_index(t_node *stack)
{
	int	i;
	int	stack_half;

	stack_half = ft_lstsize(stack) / 2;
	i = 0;
	while (stack)
	{
		stack->index = i;
		if (i <= stack_half)
			stack->upper_half = true;
		else
			stack->upper_half = false;
		i++;
		stack = stack->next;
	}
}

static	void	set_target(t_node *a, t_node *b)
{
	t_node	*tmp_a;
	t_node	*target;
	int		target_value;

	while (b)
	{
		target_value = INT_MAX; //esta variable nos ayuda a ver el siguiente mas grande mas pequeño posible 
		tmp_a = a;
		while (tmp_a)
		{
			if (b->data < tmp_a->data && tmp_a->data < target_value)
			{
				target_value = tmp_a->data;
				target = tmp_a;
			}
			tmp_a = tmp_a->next;
		}
		if (target_value == INT_MAX)
			b->target = ft_lstsmallest(a); //missing ft
		else
			b->target = target;
		b = b->next;
	}
}

static	void	comp_price(t_node *b, int size_a, int size_b)
{
	int	r_price;
	int rr_price;

	if (b->index > b->target->index)
		r_price = b->index;
	else
		r_price = b->target->index;
	if ((size_b - b->index) > (size_a - b->target->index))
		rr_price = size_b - b->index;
	else
		rr_price = size_a - b->target->index;
	if (r_price < rr_price)
		b->push_price = r_price;
	else
		b->push_price = rr_price;
}

static	void	set_price(t_node *a, t_node *b)
{
	int	size_a;
	int	size_b;

	size_a = ft_lstsize(a);
	size_b = ft_lstsize(b);
	while (b)
	{
		if (b->upper_half && b->target->upper_half)
		{
			if (b->index > b->target->index)
				b->push_price = b->index;
			else
				b->push_price = b->target->index;
		}
		else if (!b->upper_half && !b->target->upper_half)
		{
			if ((size_b - b->index) > (size_a - b->target->index))
				b->push_price = size_b - b->index;
			else
				b->push_price = size_a - b->target->index;
		}
		else
			comp_price(b, size_a, size_b);
		b = b->next;
	}
}

static	void	move_cheapest(t_node **a, t_node **b)
{
	t_node	*cheapest;
	t_node	*tmp_b;
	int		size_a;
	int		size_b;
	int		r_price;
	int		rr_price;

	cheapest = *b;
	tmp_b = *b;
	size_a = ft_lstsize(*a);
	size_b = ft_lstsize(*b);
	while (tmp_b)
	{
		if (tmp_b->push_price < cheapest->push_price)
			cheapest = tmp_b;
		tmp_b = tmp_b->next;
	}
	if (cheapest->upper_half && cheapest->target->upper_half)// los dos upper half, rotate
	{
		if (cheapest->index > cheapest->target->index)  //stack b 2 > stack a 1  >> 1 > 0  >>  0 >> 0 
 		{
			while (cheapest->target->index)
			{
				rr(a, b);
				cheapest->target->index--;
				cheapest->index--;
			}
			while (cheapest->index)
			{
				rb(b);
				cheapest->index--;
			}
		}
		else //stack b 1 > stack a 2  >> 0 > 1  >>  0 >> 0 
		{
			while (cheapest->index)
			{
				rr(a, b);
				cheapest->index--;
				cheapest->target->index--;
			}
			while (cheapest->target->index)
			{
				ra(a);
				cheapest->target->index--;
			}
		}
	}
	else if (!cheapest->upper_half && !cheapest->target->upper_half) // los dos esta abajop
	{
		if ((size_b - cheapest->index) > (size_a - cheapest->target->index)) //el resultado de cada resta te dice cual esta mas arriba 
		{
			while ((size_a - cheapest->target->index)) //iteramos inex para que el resultado de la resta de 0 y asi salir del bucle. Aqui target necesita menos movimientos
			{
				rrr(a, b);
				cheapest->target->index++;
				cheapest->index++;
			}
			while ((size_b - cheapest->index)) // queda pendiente las rotasciones de stack b pero el nodo de a ya esta en el top
			{
				rrb(b); //por eso rotamos aqui solo el del stack b
				cheapest->index++;
			}
		}
		else //caso contrario a toda la logica anterior
		{
			while ((size_b - cheapest->index) && cheapest->index) 
			{
				rrr(a, b);
				cheapest->index++;
				cheapest->target->index++;
			}
			while ((size_a - cheapest->target->index))
			{
				rra(a);
				cheapest->target->index++;
			}
		}
	}
	else //si cada uno esta en una mitad diferente 
	{
		if (cheapest->index > cheapest->target->index) //el rotate_price sera igual al index mas grande de los dos
			r_price = cheapest->index;
		else//el rotate_price sera igual al index mas grande de los dos
			r_price = cheapest->target->index;
		if ((size_b - cheapest->index) > (size_a - cheapest->target->index))//el reverse_rotate_price sera igual a la diferencia mas grande entre el size y el index
			rr_price = size_b - cheapest->index;
		else
			rr_price = size_a - cheapest->target->index;
		if (r_price < rr_price) //si es mas barato rotar, se ejecuta  toda la logica del primer if 
		{
			if (cheapest->index > cheapest->target->index)
			{
				while (cheapest->target->index)
				{
					rr(a, b);
					cheapest->target->index--;
					cheapest->index--;
				}
				while (cheapest->index)
				{
					rb(b);
					cheapest->index--;
				}
			}
			else 
			{
				while (cheapest->index)
				{
					rr(a, b);
					cheapest->index--;
					cheapest->target->index--;
				}
				while (cheapest->target->index)
				{
					ra(a);
					cheapest->target->index--;
				}
			}
		}
		else //en caso contrario se utiliza la logica del else if
		{
			if ((size_b - cheapest->index) > (size_a - cheapest->target->index))
			{
				while ((size_a - cheapest->target->index))
				{
					rrr(a, b);
					cheapest->target->index++;
					cheapest->index++;
				}
				while ((size_b - cheapest->index))
				{
					rrb(b);
					cheapest->index++;
				}
			}
			else
			{
				while ((size_b - cheapest->index) && cheapest->index)
				{
					rrr(a, b);
					cheapest->index++;
					cheapest->target->index++;
				}
				while ((size_a - cheapest->target->index))
				{
					rra(a);
					cheapest->target->index++;
				}
			}
		}
	}
	pa(a, b);
}
// casos posibles con 3 numeros =  | 3 1 2 |  2 1 3 |  3 2 1 | 1 3 2 correct | 2 3 1 correct 
void	tiny_sort(t_node **stack)
{
	if ((*stack)->next->data > (*stack)->next->next->data) // 1 3 2 correct | 2 3 1 correct 
	{
		if (((*stack)->data > (*stack)->next->data &&
		 (*stack)->data > (*stack)->next->next->data))//3 1 2
		 {
			sa(stack);
			rra(stack);
		}
		else if ((*stack)->next->data > (*stack)->data 
		&& (*stack)->next->next->data > (*stack)->data)
		{
			sa(stack);
			ra(stack);
		}
		else
			rra(stack);
	}
	else if ((*stack)->next->data < (*stack)->next->next->data) //| 3 > 1 < 2 |  2 1 3
	{
		if ((*stack)->data < (*stack)->next->next->data &&
		(*stack)->next->data < (*stack)->data)
			sa(stack);
		else
			ra(stack);
	}
}

void	push_swap(t_node **a, t_node **b)
{
	int size_a;

	size_a = ft_lstsize(*a);
	if (size_a == 3)
		return (tiny_sort(a));
	while (size_a-- > 3)
		pb(a, b);
	tiny_sort(a);
	//print_stack(a);
	//print_stack(b);
	while (*b)
	{
		set_index(*a);
		set_index(*b);
		set_target(*a, *b);
		set_price(*a, *b);
		move_cheapest(a, b);
		//print_stack(a);
		//print_stack(b);
	}
	print_stack(a);
	set_index(*a);
	if (ft_lstsmallest(*a)->upper_half)
	{
		while(ft_lstsmallest(*a) != *a)
			ra(a);
	}
	else
	{
		while(ft_lstsmallest(*a) != *a)
			rra(a);
	}
}

int	check_is_sorted(t_node **stack_a)
{
	int i;

	while((*stack_a)->next)
	{
		i = (*stack_a)->data;
		*stack_a = (*stack_a)->next;
		if ((*stack_a)->data < i)
			return (0);
	}
	return (1);
}
