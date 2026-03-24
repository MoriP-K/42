/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 20:50:03 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/01/07 23:13:22 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ra(t_stack *a)
{
	int	i;
	int	tmp;

	tmp = a->data[0];
	i = 1;
	while (i < a->len)
	{
		a->data[i - 1] = a->data[i];
		i++;
	}
	a->data[i - 1] = tmp;
}

void	rb(t_stack *b)
{
	int	i;
	int	tmp;

	tmp = b->data[0];
	i = 1;
	while (i < b->len)
	{
		b->data[i - 1] = b->data[i];
		i++;
	}
	b->data[i - 1] = tmp;
}

void	rr(t_stack *a, t_stack *b)
{
	ra(a);
	ra(b);
}
