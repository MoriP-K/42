/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 20:57:23 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/05/17 03:04:18 by kmoriyam         ###   ########.fr       */
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
	int	is_died_message;

	is_died_message = 0;
	if (ft_strcmp("died", text) == 0)
		is_died_message = 1;
	if (is_died_message == 0 && is_philo_died(philo->table))
		return ;
	if (is_died_message == 0 && is_simulation_stopped(philo->table))
		return ;
	pthread_mutex_lock(&philo->table->print_mtx);
	if (is_died_message || (!is_simulation_stopped(philo->table)
			&& !is_philo_died(philo->table)))
	{
		printf("%ld %d %s\n", now() - philo->table->start_time, philo->id,
			text);
		if (is_died_message)
		{
			pthread_mutex_lock(&philo->table->died_mtx);
			philo->table->philo_died = 1;
			pthread_mutex_unlock(&philo->table->died_mtx);
		}
	}
	pthread_mutex_unlock(&philo->table->print_mtx);
}
