/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 22:11:43 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/05/17 03:04:18 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	is_philo_died(t_table *table)
{
	int	result;

	pthread_mutex_lock(&table->died_mtx);
	result = table->philo_died;
	pthread_mutex_unlock(&table->died_mtx);
	return (result);
}

void	set_philo_died(t_table *table)
{
	pthread_mutex_lock(&table->died_mtx);
	table->philo_died = 1;
	pthread_mutex_unlock(&table->died_mtx);
}

void	destroy_all_mtx(t_table *table)
{
	t_philo	*philo;
	int		i;

	if (!table || !table->philos)
		return ;
	philo = table->philos;
	i = 0;
	while (i < table->num_of_philo)
	{
		pthread_mutex_destroy(&philo->left_fork->fork);
		pthread_mutex_destroy(&philo->meal_mtx);
		philo = philo->left_side;
		i++;
	}
	pthread_mutex_destroy(&table->print_mtx);
	pthread_mutex_destroy(&table->stop_mtx);
	pthread_mutex_destroy(&table->died_mtx);
}
