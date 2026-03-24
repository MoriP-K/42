/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 20:50:03 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/01/08 13:22:50 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "push_swap.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	ft_int(long long num, char **array, char *endptr, int is_allocated)
{
	if (*endptr != '\0' || num < INT_MIN || num > INT_MAX)
	{
		if (is_allocated)
			free(array);
		return (0);
	}
	return (1);
}

char	**set_arg(int ac, char **av, t_stack *a, int *is_alloated)
{
	char	**array;

	*is_alloated = 0;
	if (ac == 2 && ft_strchr(av[1], ' '))
	{
		array = ft_split(av[1], ' ');
		if (!array)
			return (NULL);
		a->len = (int)ft_arrlen(array);
		*is_alloated = 1;
	}
	else
	{
		array = &av[1];
		a->len = ac - 1;
	}
	return (array);
}

int	validate_arg(int ac, char **av, t_stack *a)
{
	int			i;
	long long	num;
	int			is_allocated;
	char		*endptr;
	char		**array;

	array = set_arg(ac, av, a, &is_allocated);
	if (!array)
		return (0);
	i = 0;
	while (i < a->len)
	{
		if (!ft_isint(array[i]))
			return (0);
		endptr = NULL;
		num = ft_strtol(array[i], &endptr);
		if (!ft_int(num, array, endptr, is_allocated))
			return (0);
		a->data[i++] = (int)num;
	}
	if (is_allocated)
		free_array(array);
	if (check_double(a))
		return (0);
	return (1);
}
