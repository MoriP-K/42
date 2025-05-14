/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_lifecycle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 21:58:29 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/05/14 22:01:32 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	time_to_take(long mileseconds)
{
	long	start;
	long	current;

	start = now();
	while (1)
	{
		current = now();
		if (current - start >= mileseconds)
			break ;
		usleep(500);
	}
}

static void	put_down_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->left_fork->fork);
	pthread_mutex_unlock(&philo->right_fork->fork);
}

static void	eat(t_philo *philo)
{
	print_status(philo, "is eating");
	pthread_mutex_lock(&philo->meal_mtx);
	philo->last_meal_time = now();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mtx);
	time_to_take(philo->table->time_to_eat);
}

static void	take_forks(t_philo *philo)
{
	if (philo->table->num_of_philo == 1)
	{
		pthread_mutex_lock(&philo->left_fork->fork);
		print_status(philo, "has taken a fork");
		while (!is_simulation_stopped(philo->table))
			usleep(1000);
		pthread_mutex_unlock(&philo->left_fork->fork);
		return ;
	}
	if (philo->id % 2 == 0)
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
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!is_simulation_stopped(philo->table))
	{
		print_status(philo, "is thinking");
		take_forks(philo);
		eat(philo);
		put_down_forks(philo);
		print_status(philo, "is sleeping");
		time_to_take(philo->table->time_to_sleep);
	}
	return (NULL);
}
