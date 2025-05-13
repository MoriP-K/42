/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 20:22:01 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/05/13 22:11:20 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int		sum = 0;

long	now(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	parse_input_to_table(t_table *table, char **av)
{
	table->num_of_philo = ft_atoi(av[1], table);
	table->time_to_die = ft_atoi(av[2], table);
	table->time_to_eat = ft_atoi(av[3], table);
	table->time_to_sleep = ft_atoi(av[4], table);
	if (av[5])
		table->nbr_limit_meals = ft_atoi(av[5], table);
	else
		table->nbr_limit_meals = -1;
}

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

void	debug(t_table *table)
{
	printf("nbr: %ld\n", table->num_of_philo);
	printf("die: %ld\n", table->time_to_die);
	printf("eat: %ld\n", table->time_to_eat);
	printf("sleep: %ld\n", table->time_to_sleep);
	printf("meals: %ld\n", table->nbr_limit_meals);
}

void	debug_philo(t_table *table, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < table->num_of_philo)
	{
		printf("id: %d\n", philo->id);
		philo = philo->left_side;
		i++;
	}
}

void	stop_simulation(t_table *table)
{
	pthread_mutex_lock(&table->stop_mtx);
	table->simulation_stop = 1;
	pthread_mutex_unlock(&table->stop_mtx);
}

int	is_simulation_stopped(t_table *table)
{
	int	result;

	pthread_mutex_lock(&table->stop_mtx);
	result = table->simulation_stop;
	pthread_mutex_unlock(&table->stop_mtx);
	return (result);
}

void	print_status(t_philo *philo, char *text)
{
	if (is_simulation_stopped(philo->table))
		return ;
	pthread_mutex_lock(&philo->table->print_mtx);
	if (!is_simulation_stopped(philo->table))
		printf("%ld %d %s\n",
			now() - philo->table->start_time,
			philo->id,
			text);
	pthread_mutex_unlock(&philo->table->print_mtx);
}

void	sleeeeep(long mileseconds)
{
	long	start;
	long	current;

	start = now();
	while (1)
	{
		current = now();
		if (current - start >= mileseconds)
			break;
		usleep(500);
	}
}

void	put_down_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->left_fork->fork);
	pthread_mutex_unlock(&philo->right_fork->fork);
}

void	eat(t_philo *philo)
{
	print_status(philo, "is eating");
	pthread_mutex_lock(&philo->meal_mtx);
	philo->last_meal_time = now();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mtx);
	sleeeeep(philo->table->time_to_eat);
}

void	take_forks(t_philo *philo)
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

void	*philosopher_lifecycle(void *arg)
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
		sum++;
		put_down_forks(philo);
		print_status(philo, "is sleeping");
		sleeeeep(philo->table->time_to_sleep);
	}
	return (NULL);
}

void	init_table(t_table *table)
{
	table->start_time = now();
	table->simulation_stop = 0;
	pthread_mutex_init(&table->print_mtx, NULL);
	pthread_mutex_init(&table->stop_mtx, NULL);
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
	return (meals_done);
}

void	*monitor_philos(void *arg)
{
	t_table *table;
	t_philo	*philo;
	int		i;

	table = (t_table *)arg;
	while (1)
	{
		i = 0;
		philo = table->philos;
		if (all_philos_ate_enough(table))
		{
			stop_simulation(table);
			return (NULL);
		}
		while (i < table->num_of_philo)
		{
			if (is_philo_dead(philo))
			{
				print_status(philo, "died");
				stop_simulation(table);
				return (NULL);
			}
			philo = philo->left_side;
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}

void	destroy_all_mtx(t_table *table)
{
	t_philo	*philo;
	int		i;

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

void	init_mtx_philos(t_table *table)
{
	t_philo		*philos;
	int	i;

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

void	create_threads_philos(t_table *table)
{
	t_philo	*philos;
	int	i;

	i = 0;
	philos = table->philos;
	// debug_philo(table, philos);
	while (i < table->num_of_philo)
	{
		pthread_create(&philos->p_id, NULL, philosopher_lifecycle, philos);
		philos = philos->left_side;
		i++;
		// printf("index: %d\n", i);
	}
}

void	monitor_philos(t_table *table)
{
	pthread_t	monitor;

	// create threads for monitor
	pthread_create(&monitor, NULL, monitor_philos, table);
	pthread_join(monitor, NULL);
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

void	destroy_mtx_philos(t_table *table)
{
	t_philo	*philos;
	int		i;

	i = 0;
	while (i < table->num_of_philo)
	{
		pthread_mutex_destroy(&philos->left_fork->fork);
		philos = philos->left_side;
		i++;
	}
}

void	start_dinner(t_table *table)
{
	init_table(table);
	init_mtx_philos(table);
	create_threads_philos(table);
	monitor_philos(table);
	wait_threads_philos(table);
	destroy_mtx_philos(table);
	destroy_all_mtx(table);
}

// ./philo [nbr] [die] [eat] [sleep] [eat_time]
int	main(int ac, char *av[])
{
	t_table	table;

	if (ac == 5 || ac == 6)
	{
		parse_input_to_table(&table, av);
		// debug(&table);
		init_philo(&table, &table.philos);
		start_dinner(&table);
		free_table(&table);
	}
	else
		error_exit("Invalid argument, innit??", &table);
	return (0);
}

// Do not test with more than 200 philosophers. 
// Do not test with time_to_die or time_to_eat or time_to_sleep
// set to values lower than 60 ms. Test 1 800 200 200.
// The philosopher should not eat and should die.
// Test 5 800 200 200. No philosopher should die.
// Test 5 800 200 200 7. No philosopher should die and
// the simulation should stop when every philosopher has eaten at least 7 times.
// Test 4 410 200 200. No philosopher should die. 
// Test 4 310 200 100. One philosopher should die. 
// Test with 2 philosophers and check the different times:
// a death delayed by more than 10 ms is unacceptable.
// Test with any values of your choice to verify all the requirements.
// Ensure philosophers die at the right time,
// that they don't steal forks, and so forth.