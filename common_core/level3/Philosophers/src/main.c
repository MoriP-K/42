/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 20:22:01 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/05/14 22:12:59 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	parse_input_to_table(t_table *table, char **av)
{
	table->num_of_philo = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		table->nbr_limit_meals = ft_atoi(av[5]);
	else
		table->nbr_limit_meals = -1;
}

void	start_dinner(t_table *table)
{
	init_table(table);
	init_mtx_philos(table);
	create_threads_philos(table);
	monitor_philos_status(table);
	wait_threads_philos(table);
	destroy_all_mtx(table);
}

int	main(int ac, char *av[])
{
	t_table	table;

	if (ac == 5 || ac == 6)
	{
		parse_input_to_table(&table, av);
		init_philo(&table, &table.philos);
		start_dinner(&table);
		free_table(&table);
	}
	else
		error_exit("Invalid argument, innit??", &table);
	return (0);
}
