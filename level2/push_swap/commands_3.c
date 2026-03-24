/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 20:50:03 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/01/07 23:13:41 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rra(t_stack *a)
{
	int	i;
	int	tmp;

	tmp = a->data[a->len - 1];
	i = 1;
	while (i < a->len)
	{
		a->data[a->len - i] = a->data[a->len - i - 1];
		i++;
	}
	a->data[0] = tmp;
}

void	rrb(t_stack *b)
{
	int	i;
	int	tmp;

	tmp = b->data[b->len - 1];
	i = 1;
	while (i < b->len)
	{
		b->data[b->len - i] = b->data[b->len - i - 1];
		i++;
	}
	b->data[0] = tmp;
}

void	rrr(t_stack *a, t_stack *b)
{
	rra(a);
	rrb(b);
}
