/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 20:50:03 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/01/08 13:19:25 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "push_swap.h"

void	sort(int *compressed, t_stack *a)
{
	int	i;
	int	j;
	int	tmp;

	i = 0;
	tmp = 0;
	while (i < a->len - 1)
	{
		j = 0;
		while (j < a->len - i - 1)
		{
			if (compressed[j] > compressed[j + 1])
				sa(&compressed[j]);
			j++;
		}
		i++;
	}
}

int	*numcpy(int *dest, t_stack *a)
{
	int	i;

	i = 0;
	while (i < a->len)
	{
		dest[i] = a->data[i];
		i++;
	}
	return (dest);
}

int	assign_index(int *copmressed, int num, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (copmressed[i] == num)
			return (i);
		i++;
	}
	return (0);
}

void	compress_stack(t_stack *a)
{
	int	*compressed;
	int	i;

	compressed = malloc(sizeof(int) * a->len);
	if (!compressed)
		return ;
	compressed = numcpy(compressed, a);
	sort(compressed, a);
	i = 0;
	while (i < a->len)
	{
		a->data[i] = assign_index(compressed, a->data[i], a->len);
		i++;
	}
	free(compressed);
}

void	start_sort(t_stack *a, t_stack *b, t_list **cmd_lists)
{
	compress_stack(a);
	if (a->len == 2)
		sort_two(a, b, cmd_lists);
	else if (a->len == 3)
		sort_three(a, b, cmd_lists);
	else if (a->len == 4)
		sort_four(a, b, cmd_lists);
	else if (a->len <= 6)
		sort_more_than_five(a, b, cmd_lists);
	else
		sort_by_chunky(a, b, cmd_lists);
}
