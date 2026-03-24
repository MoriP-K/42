/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 20:50:03 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/01/08 16:50:08 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "push_swap.h"

int	main(int ac, char **av)
{
	t_stack	*a;
	t_stack	*b;
	t_list	*cmd_lists;

	if (ac == 1 || ac > 50001)
		exit(EXIT_SUCCESS);
	if (!init_structure(&a, &b, &cmd_lists) || !validate_arg(ac, av, a))
	{
		ft_putendl_fd("Error", 2);
		free_structure(&a, &b, &cmd_lists);
		return (1);
	}
	if (is_sorted(a))
	{
		free_structure(&a, &b, &cmd_lists);
		return (0);
	}
	start_sort(a, b, &cmd_lists);
	print_cmds(cmd_lists);
	free_structure(&a, &b, &cmd_lists);
	return (0);
}
