/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_by_chunky.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 20:50:03 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/01/08 19:24:58 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "push_swap.h"

int	count_range(t_stack *a, int min, int max)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (i < a->len)
	{
		if (min <= a->data[i] && a->data[i] < max)
			count++;
		i++;
	}
	return (count);
}

int	is_in_range(int num, int min, int max)
{
	return (min <= num && num < max);
}

int	split_chunk_size(int len)
{
	int	chunk_size;

	chunk_size = 0;
	if (len <= 100)
		chunk_size = len / 5;
	else
		chunk_size = len / 10;
	return (chunk_size);
}

void	exec_pb_rb(t_stack *a, t_stack *b, t_list **cmd_lists)
{
	exec_cmd(PB, a, b, cmd_lists);
	exec_cmd(RB, a, b, cmd_lists);
}

void	sort_by_chunky(t_stack *a, t_stack *b, t_list **cmd_lists)
{
	int	chunk_size;
	int	chunks;
	int	i;
	int	min;
	int	max;

	chunk_size = split_chunk_size(a->len);
	chunks = a->len / chunk_size + 1;
	i = 0;
	while (i < chunks)
	{
		min = i * chunk_size;
		max = (i++ + 1) * chunk_size;
		while (count_range(a, min, max) > 0)
		{
			if (is_in_range(a->data[0], min + chunk_size / 2, max))
				exec_cmd(PB, a, b, cmd_lists);
			else if (is_in_range(a->data[0], min, min + chunk_size / 2))
				exec_pb_rb(a, b, cmd_lists);
			else
				exec_cmd(RA, a, b, cmd_lists);
		}
	}
	while (b->len)
		search_max_pa(a, b, cmd_lists);
}
