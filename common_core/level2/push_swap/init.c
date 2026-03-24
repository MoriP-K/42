/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 20:50:03 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/01/08 13:21:22 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "push_swap.h"

void	free_structure(t_stack **a, t_stack **b, t_list **cmd_lists)
{
	if (*a)
	{
		free(*a);
		*a = NULL;
	}
	if (*b)
	{
		free(*b);
		*b = NULL;
	}
	if (cmd_lists)
	{
		ft_lstclear(cmd_lists, free);
		*cmd_lists = NULL;
	}
}

int	init_structure(t_stack **a, t_stack **b, t_list **cmd_lists)
{
	*a = malloc(sizeof(t_stack));
	*b = malloc(sizeof(t_stack));
	*cmd_lists = NULL;
	if (!*a || !*b)
	{
		if (*a)
			free(*a);
		if (*b)
			free(*b);
		return (0);
	}
	(*a)->len = 0;
	ft_bzero((*a)->data, sizeof((*a)->data));
	(*b)->len = 0;
	ft_bzero((*b)->data, sizeof((*b)->data));
	return (1);
}
