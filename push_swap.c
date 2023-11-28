/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-tole <ade-tole@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:06:05 by ade-tole          #+#    #+#             */
/*   Updated: 2023/11/26 23:29:08 by ade-tole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

//Return the dir about min data node on stack to set the target
static t_node	*list_lstsmallest(t_node *stack)
{
	int i;
	t_node *tmp;

	tmp = stack;

	while (stack)
	{
		if (stack->data > tmp->data)
			tmp = stack;
		stack = stack->next;
	}
	return (tmp);
}

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
//de cada nodo en b busca el siguiente mas grande en a, si no lo encuentra busca el mas pequeño en a
static	void	set_target(t_node *a, t_node *b)
{
	t_node	*tmp_b;
	t_node	*target;
	int		target_value;//Almacena el valor del nodo mas grande

	while (a)
	{
		target_value = INT_MAX;// para asegurarme que se ael siguiente mas grande y no saltar nodos
		tmp_b = b;
		while (tmp_b)
		{
			if ((tmp_b->data > b->data) && (tmp_b->data < target_value))// mas grande y menor que el tope del registro de todo el stack a
			{
				target_value = tmp_b->data; //96 
				target = tmp_b; //nodo objetivo es 96
			}
			tmp_b = tmp_b->next;
		}
		if (target_value == INT_MAX) //no
			b->target = ft_lstsmallest(b); //
		else
			a->target = target; //
		a = a->next;
	}
}
void	comp_price(t_node *a, t_node *b, int size_a, int size_b)
{
	int	r_price;
	int rr_price;

	if (a->index > a->target->index)
		r_price = a->index;
	else
		r_price = a->target->index;
	if ((size_a - a->index) > (size_b - a->target->index))
		rr_price = size_a - a->index;
	else
		rr_price = size_b - a->target->index;
	if (r_price < rr_price)
		a->push_price = r_price;
	else
		a->push_price = rr_price;
}
void	set_price(t_node *a, t_node *b)
{
	int	size_a;
	int	size_b;

	size_a = ft_lstsize(a);
	size_b = ft_lstsize(b);
	while (a)
	{
		if (a->upper_half && a->target->upper_half)// los dos upper
		{
			if (a->index > a->target->index)//nos quedamos con el mayor ya que permite hacer rr both
				a->push_price = a->index;
			else
				a->push_price = a->target->index;
		}
		else if (!a->upper_half && !a->target->upper_half)
		{
			if ((size_a - a->index) > (size_b - a->target->index))
				a->push_price = size_a - a->index;
			else
				a->push_price = size_b - a->target->index;
		}
		else
			comp_price(a, b, size_a, size_b);
		a = a->next;
	}
}
void	set_cheapest(t_node *stack)
{
	int	push_price_min;
	t_node *cheapest_node;

	push_price_min = INT_MAX;
	while (stack)
	{
		if (stack->push_price < push_price_min)
			push_price_min = stack->push_price;
		stack = stack->next;
		cheapest_node = stack;	
	}
	cheapest_node->cheapest = true;
}


void	push_swap(t_node **a, t_node **b)
{
	pb(a, b);
	pb(a, b);

	while (*a)
	{
		set_index(*a);
		set_index(*b);
		set_target(*a, *b);
	}
}
