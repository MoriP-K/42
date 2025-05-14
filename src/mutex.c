/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 22:11:43 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/05/14 22:12:07 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

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
}
