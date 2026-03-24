/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_lifecycle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 21:58:29 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/05/17 03:15:49 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	time_to_take_with_check(long mileseconds, t_table *table)
{
	long	start;
	long	current;

	start = now();
	while (!is_simulation_stopped(table) && !is_philo_died(table))
	{
		current = now();
		if (current - start >= mileseconds)
			break ;
		usleep(500);
	}
}

void	put_down_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->left_fork->fork);
	if (philo->table->num_of_philo > 1)
		pthread_mutex_unlock(&philo->right_fork->fork);
}

static void	eat(t_philo *philo)
{
	print_status(philo, "is eating");
	pthread_mutex_lock(&philo->meal_mtx);
	philo->last_meal_time = now();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mtx);
	time_to_take_with_check(philo->table->time_to_eat, philo->table);
}

static void	take_forks(t_philo *philo)
{
	if (philo->left_fork->id < philo->right_fork->id)
	{
		pthread_mutex_lock(&philo->right_fork->fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(&philo->left_fork->fork);
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->left_fork->fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(&philo->right_fork->fork);
		print_status(philo, "has taken a fork");
	}
}

void	*philo_lifecycle(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (!is_single_philo(philo))
		return (NULL);
	if (philo->id % 2 == 0)
		usleep(10000);
	while (!is_simulation_stopped(philo->table) && !is_philo_died(philo->table))
	{
		print_status(philo, "is thinking");
		if (is_simulation_stopped(philo->table) || is_philo_died(philo->table))
			break ;
		take_forks(philo);
		if (stop_lifecycle(philo->table, philo))
			break ;
		eat(philo);
		if (stop_lifecycle(philo->table, philo))
			break ;
		put_down_forks(philo);
		if (is_simulation_stopped(philo->table) || is_philo_died(philo->table))
			break ;
		print_status(philo, "is sleeping");
		time_to_take_with_check(philo->table->time_to_sleep, philo->table);
	}
	return (NULL);
}
