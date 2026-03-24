/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_normal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 20:50:03 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/01/08 13:19:40 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "push_swap.h"

void	sort_two(t_stack *a, t_stack *b, t_list **cmd_lists)
{
	if (a->data[0] > a->data[1])
		exec_cmd(SA, a, b, cmd_lists);
}

void	sort_three(t_stack *a, t_stack *b, t_list **cmd_lists)
{
	int	max_index;

	max_index = search_max_index(a);
	if (max_index == 0)
	{
		exec_cmd(RA, a, b, cmd_lists);
		if (a->data[0] > a->data[1])
			exec_cmd(SA, a, b, cmd_lists);
	}
	else if (max_index == 1)
	{
		exec_cmd(RRA, a, b, cmd_lists);
		if (a->data[0] > a->data[1])
			exec_cmd(SA, a, b, cmd_lists);
	}
	else if (max_index == 2 && a->data[0] > a->data[1])
		exec_cmd(SA, a, b, cmd_lists);
}

void	sort_four(t_stack *a, t_stack *b, t_list **cmd_lists)
{
	search_min_pb(a, b, cmd_lists);
	sort_three(a, b, cmd_lists);
	exec_cmd(PA, a, b, cmd_lists);
}

void	sort_more_than_five(t_stack *a, t_stack *b, t_list **cmd_lists)
{
	while (a->len > 3)
		search_min_pb(a, b, cmd_lists);
	sort_three(a, b, cmd_lists);
	while (b->len)
		exec_cmd(PA, a, b, cmd_lists);
}
