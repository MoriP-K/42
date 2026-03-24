/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 20:50:03 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/01/08 13:19:21 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "push_swap.h"

void	check_cmds(t_list *cmd_lists)
{
	t_list	*current;

	current = cmd_lists;
	while (current)
	{
		if (current->next != NULL
			&& ((current->data == RA && current->next->data == RB)
				|| (current->data == RB && current->next->data == RA)))
		{
			current->data = RR;
			current->next->data = NONE;
		}
		current = current->next;
	}
}

void	write_cmd(t_command cmd)
{
	if (cmd == SA)
		write(1, "sa\n", 3);
	else if (cmd == SB)
		write(1, "sb\n", 3);
	else if (cmd == SS)
		write(1, "ss\n", 3);
	else if (cmd == RA)
		write(1, "ra\n", 3);
	else if (cmd == RB)
		write(1, "rb\n", 3);
	else if (cmd == RR)
		write(1, "rr\n", 3);
	else if (cmd == RRA)
		write(1, "rra\n", 4);
	else if (cmd == RRB)
		write(1, "rrb\n", 4);
	else if (cmd == RRR)
		write(1, "rrr\n", 4);
	else if (cmd == PA)
		write(1, "pa\n", 3);
	else if (cmd == PB)
		write(1, "pb\n", 3);
}

void	print_cmds(t_list *cmd_lists)
{
	t_list		*current;
	t_command	cmd;

	current = cmd_lists;
	while (current)
	{
		check_cmds(cmd_lists);
		if (current->data == NONE)
			current = current->next;
		cmd = current->data;
		write_cmd(cmd);
		current = current->next;
	}
}

void	add_cmd(t_list **cmd_lists, t_command cmd)
{
	t_list	*node;

	node = ft_lstnew(cmd);
	if (!node)
		return ;
	ft_lstadd_back(cmd_lists, node);
}

void	exec_cmd(t_command cmd, t_stack *a, t_stack *b, t_list **cmd_lists)
{
	if (cmd == SA || cmd == SB || cmd == SS)
		exec_swap(a, b, cmd);
	else if (cmd == RA || cmd == RB || cmd == RR)
		exec_rotate(a, b, cmd);
	else if (cmd == RRA || cmd == RRB || cmd == RRR)
		exec_reverse_rotate(a, b, cmd);
	else if (cmd == PA || cmd == PB)
		exec_push(a, b, cmd);
	add_cmd(cmd_lists, cmd);
}
