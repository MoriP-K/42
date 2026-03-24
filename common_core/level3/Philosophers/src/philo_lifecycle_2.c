/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_lifecycle_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 03:13:17 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/05/17 03:13:56 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*is_single_philo(t_philo *philo)
{
	if (philo->table->num_of_philo == 1)
	{
		print_status(philo, "is thinking");
		pthread_mutex_lock(&philo->left_fork->fork);
		print_status(philo, "has taken a fork");
		while (!is_simulation_stopped(philo->table))
			usleep(1000);
		pthread_mutex_unlock(&philo->left_fork->fork);
		return (NULL);
	}
	return (philo);
}

int	stop_lifecycle(t_table *table, t_philo *philo)
{
	if (is_simulation_stopped(table) || is_philo_died(table))
	{
		put_down_forks(philo);
		return (1);
	}
	return (0);
}
