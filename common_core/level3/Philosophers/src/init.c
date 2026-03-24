/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 22:08:28 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/05/16 22:49:59 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	assign_fork(t_table *table)
{
	t_philo	*tmp;
	t_fork	*next_right_fork;
	int		i;

	tmp = table->philos;
	next_right_fork = NULL;
	i = 0;
	while (i < table->num_of_philo)
	{
		if (i != 0)
			tmp->right_fork = next_right_fork;
		tmp->left_fork = ft_malloc(sizeof(t_fork), table);
		tmp->left_fork->id = i + 1;
		next_right_fork = tmp->left_fork;
		tmp = tmp->left_side;
		i++;
	}
	tmp->right_fork = next_right_fork;
}

void	init_philo(t_table *table, t_philo **head)
{
	t_philo	*new_philo;
	t_philo	*prev;
	int		i;

	*head = NULL;
	new_philo = NULL;
	prev = NULL;
	i = 0;
	while (i < table->num_of_philo)
	{
		new_philo = new_philo_list(table);
		new_philo->id = i + 1;
		add_philo_list(head, new_philo, prev, table);
		prev = new_philo;
		i++;
	}
	assign_fork(table);
}

void	init_mtx_philos(t_table *table)
{
	t_philo	*philos;
	int		i;

	philos = table->philos;
	i = 0;
	while (i < table->num_of_philo)
	{
		pthread_mutex_init(&philos->left_fork->fork, NULL);
		pthread_mutex_init(&philos->meal_mtx, NULL);
		philos->table = table;
		philos->last_meal_time = now();
		philos->meals_eaten = 0;
		philos = philos->left_side;
		i++;
	}
}

void	init_table(t_table *table)
{
	table->simulation_stop = 0;
	table->philo_died = 0;
	pthread_mutex_init(&table->print_mtx, NULL);
	pthread_mutex_init(&table->stop_mtx, NULL);
	pthread_mutex_init(&table->died_mtx, NULL);
	table->start_time = now();
}
