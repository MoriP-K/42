/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_limit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 20:50:03 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/01/07 23:16:25 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "push_swap.h"

int	search_max_index(t_stack *stack)
{
	int	i;
	int	max;
	int	index;

	i = 0;
	max = 0;
	index = 0;
	while (i < stack->len)
	{
		if (max < stack->data[i])
		{
			max = stack->data[i];
			index = i;
		}
		i++;
	}
	return (index);
}

int	search_min_index(t_stack *stack)
{
	int	i;
	int	min;
	int	index;

	i = 0;
	min = stack->data[0];
	index = 0;
	while (i < stack->len)
	{
		if (min > stack->data[i])
		{
			min = stack->data[i];
			index = i;
		}
		i++;
	}
	return (index);
}

void	search_min_pb(t_stack *a, t_stack *b, t_list **cmd_lists)
{
	int	min_index;

	min_index = search_min_index(a);
	if (min_index < a->len / 2)
	{
		while (min_index)
		{
			exec_cmd(RA, a, b, cmd_lists);
			min_index--;
		}
	}
	else
	{
		while (a->len > min_index)
		{
			exec_cmd(RRA, a, b, cmd_lists);
			min_index++;
		}
	}
	exec_cmd(PB, a, b, cmd_lists);
}

void	search_max_pa(t_stack *a, t_stack *b, t_list **cmd_lists)
{
	int	max_index;

	max_index = search_max_index(b);
	if (max_index <= b->len / 2)
	{
		while (max_index)
		{
			exec_cmd(RB, a, b, cmd_lists);
			max_index--;
		}
	}
	else
	{
		while (b->len > max_index)
		{
			exec_cmd(RRB, a, b, cmd_lists);
			max_index++;
		}
	}
	exec_cmd(PA, a, b, cmd_lists);
}
