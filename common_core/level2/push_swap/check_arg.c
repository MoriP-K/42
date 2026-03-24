/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 20:50:03 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/01/08 13:25:56 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_sorted(t_stack *a)
{
	int	i;

	i = 0;
	while (i < a->len - 1)
	{
		if (a->data[i] > a->data[i + 1])
			return (0);
		i++;
	}
	return (1);
}

int	check_double(t_stack *a)
{
	int	i;
	int	j;

	i = 0;
	while (i < a->len)
	{
		j = i + 1;
		while (j < a->len)
		{
			if (a->data[i] == a->data[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
