/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 21:59:55 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/05/14 22:00:23 by kmoriyam         ###   ########.fr       */
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
}
