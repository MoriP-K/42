/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 22:11:17 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/05/17 03:01:58 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	create_threads_philos(t_table *table)
{
	t_philo	*philos;
	int		i;
	long	current_time;

	i = 0;
	philos = table->philos;
	current_time = now();
	while (i < table->num_of_philo)
	{
		pthread_mutex_lock(&philos->meal_mtx);
		philos->last_meal_time = current_time;
		pthread_mutex_unlock(&philos->meal_mtx);
		pthread_create(&philos->p_id, NULL, philo_lifecycle, philos);
		philos = philos->left_side;
		i++;
	}
}

void	wait_threads_philos(t_table *table)
{
	t_philo	*philos;
	int		i;

	i = 0;
	philos = table->philos;
	while (i < table->num_of_philo)
	{
		pthread_join(philos->p_id, NULL);
		philos = philos->left_side;
		i++;
	}
}
