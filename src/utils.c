/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 20:57:23 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/05/14 22:03:28 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

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

long	now(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	is_simulation_stopped(t_table *table)
{
	int	result;

	pthread_mutex_lock(&table->stop_mtx);
	result = table->simulation_stop;
	pthread_mutex_unlock(&table->stop_mtx);
	return (result);
}

void	print_status(t_philo *philo, char *text)
{
	if (is_simulation_stopped(philo->table))
		return ;
	pthread_mutex_lock(&philo->table->print_mtx);
	if (!is_simulation_stopped(philo->table))
		printf("%ld %d %s\n", now() - philo->table->start_time, philo->id,
			text);
	pthread_mutex_unlock(&philo->table->print_mtx);
}
