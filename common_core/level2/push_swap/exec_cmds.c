/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 20:50:03 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/01/08 13:19:17 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "push_swap.h"

void	exec_swap(t_stack *a, t_stack *b, t_command cmd)
{
	if (cmd == SA)
		sa(&a->data[0]);
	else if (cmd == SB)
		sb(&b->data[0]);
	else if (cmd == SS)
		ss(&a->data[0], &b->data[0]);
}

void	exec_rotate(t_stack *a, t_stack *b, t_command cmd)
{
	if (cmd == RA)
		ra(a);
	else if (cmd == RB)
		rb(b);
	else if (cmd == RR)
		rr(a, b);
}

void	exec_reverse_rotate(t_stack *a, t_stack *b, t_command cmd)
{
	if (cmd == RRA)
		rra(a);
	else if (cmd == RRB)
		rrb(b);
	else if (cmd == RRR)
		rrr(a, b);
}

void	exec_push(t_stack *a, t_stack *b, t_command cmd)
{
	if (cmd == PA)
		pa(a, b);
	else if (cmd == PB)
		pb(a, b);
}
