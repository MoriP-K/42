/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 22:06:16 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/05/17 03:06:16 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	stop_simulation(t_table *table)
{
	pthread_mutex_lock(&table->stop_mtx);
	table->simulation_stop = 1;
	pthread_mutex_unlock(&table->stop_mtx);
}

int	is_philo_dead(t_philo *philo)
{
	long	current_time;
	long	last_meal;

	current_time = now();
	pthread_mutex_lock(&philo->meal_mtx);
	last_meal = philo->last_meal_time;
	pthread_mutex_unlock(&philo->meal_mtx);
	if (current_time - last_meal > philo->table->time_to_die)
		return (1);
	return (0);
}

int	all_philos_ate_enough(t_table *table)
{
	t_philo	*philo;
	int		i;
	int		meals_done;

	if (table->nbr_limit_meals < 0)
		return (0);
	philo = table->philos;
	i = 0;
	meals_done = 1;
	while (i < table->num_of_philo)
	{
		pthread_mutex_lock(&philo->meal_mtx);
		if (philo->meals_eaten < table->nbr_limit_meals)
		{
			meals_done = 0;
			pthread_mutex_unlock(&philo->meal_mtx);
			break ;
		}
		pthread_mutex_unlock(&philo->meal_mtx);
		philo = philo->left_side;
		i++;
	}
	if (meals_done)
		stop_simulation(table);
	return (meals_done);
}

void	*monitoring_philos(void *arg)
{
	t_table	*table;
	t_philo	*philo;
	int		i;

	table = (t_table *)arg;
	while (!is_simulation_stopped(table))
	{
		i = 0;
		philo = table->philos;
		if (all_philos_ate_enough(table))
			return (NULL);
		while (i < table->num_of_philo && !is_simulation_stopped(table))
		{
			if (is_philo_dead(philo))
			{
				set_philo_died(table);
				print_status(philo, "died");
				stop_simulation(table);
				return (NULL);
			}
			philo = philo->left_side;
			i++;
		}
	}
	return (NULL);
}

void	monitor_philos_status(t_table *table)
{
	pthread_t	monitor;

	pthread_create(&monitor, NULL, monitoring_philos, table);
	pthread_join(monitor, NULL);
}
