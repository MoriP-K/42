/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 20:50:03 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/01/07 23:11:13 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sa(int *a)
{
	int	tmp;
	int	i;

	i = 0;
	tmp = a[i];
	a[i] = a[i + 1];
	a[i + 1] = tmp;
}

void	sb(int *b)
{
	int	tmp;
	int	i;

	i = 0;
	tmp = b[i];
	b[i] = b[i + 1];
	b[i + 1] = tmp;
}

void	ss(int *a, int *b)
{
	sb(a);
	sb(b);
}

void	pa(t_stack *a, t_stack *b)
{
	int	i;
	int	tmp;

	if (b->len == 0)
		return ;
	tmp = b->data[0];
	b->len--;
	i = 0;
	while (i < b->len)
	{
		b->data[i] = b->data[i + 1];
		i++;
	}
	a->len++;
	i = 1;
	while (i < a->len)
	{
		a->data[a->len - i] = a->data[a->len - i - 1];
		i++;
	}
	a->data[0] = tmp;
}

void	pb(t_stack *a, t_stack *b)
{
	int	i;
	int	tmp;

	if (a->len == 0)
		return ;
	tmp = a->data[0];
	a->len--;
	i = 0;
	while (i < a->len)
	{
		a->data[i] = a->data[i + 1];
		i++;
	}
	b->len++;
	i = 1;
	while (i < b->len)
	{
		b->data[b->len - i] = b->data[b->len - i - 1];
		i++;
	}
	b->data[0] = tmp;
}
