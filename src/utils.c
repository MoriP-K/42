/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 20:57:23 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/05/11 15:09:50 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	free_philos(t_philo **philo, t_table *table)
{
	t_philo	*current;
	t_philo	*start;
	t_philo	*tmp;
	int		i;

	if (!*philo)
		return ;
	current = *philo;
	start = *philo;
	i = 0;
	while (i < table->num_of_philo)
	{
		tmp = current->left_side;
		if (current->left_fork)
			free(current->left_fork);
		free(current);
		current = tmp;
		i++;
	}
	*philo = NULL;
}

void	free_table(t_table *table)
{
	if (table)
	{
		if (table->philos)
		{
			free_philos(&table->philos, table);
		}
	}
	printf("done free all!!\n");
}

void	error_exit(char *s, t_table *table)
{
	printf("%s\n", s);
	free_table(table);
	exit(EXIT_FAILURE);
}

void	*ft_malloc(size_t bytes, t_table *table)
{
	void	*ptr;

	ptr = malloc(bytes);
	if (!ptr)
		error_exit("malloc error.", table);
	return (ptr);
}

static int	is_space(char c)
{
	return ((9 <= c && c <= 13) || c == 32);
}

static int	is_digit(char c)
{
	return ('0' <= c && c <= '9');
}

int	ft_atoi(char *str, t_table *table)
{
	size_t	i;
	long	num;

	i = 0;
	while(is_space(str[i]))
		i++;
	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			error_exit("input positive number!!", table);
		i++;
	}
	if (!is_digit(str[i]))
		error_exit("input number plzzz!!", table);
	num = 0;
	while (is_digit(str[i]))
	{
		if (INT_MAX < num + (str[i] - '0'))
			error_exit("input number up to INT_MAX!!", table);
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return (num);
}
