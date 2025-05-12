/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 20:22:01 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/05/12 22:08:33 by kmoriyam         ###   ########.fr       */
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
	table->philos = NULL;
	table->start_time = now();
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
		// printf("id: %d\n", philo->id);
		philo = philo->left_side;
		i++;
	}
	printf("sum: %d\n", sum);
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

resume here;
void	print_status(t_philo *philo, char *text)
{
	printf("%ld %d %s\n", philo->table->start_time, philo->id, text);
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

void	start_dinner(t_table *table)
{
	t_philo	*philos;
	int		i;

	philos = table->philos;
	i = 0;
	while (i < table->num_of_philo)
	{
		pthread_mutex_init(&philos->left_fork->fork, NULL);
		philos = philos->left_side;
		i++;
	}
	i = 0;
	while (i < table->num_of_philo)
	{
		pthread_create(&philos->p_id, NULL, philosopher_lifecycle, philos);
		// pthread_create(&philos->p_id, NULL, philosopher_lifecycle, philos->right_fork);
		philos = philos->left_side;
		i++;
		// printf("index: %d\n", i);
	}
	i = 0;
	while (i < table->num_of_philo)
	{
		pthread_join(philos->p_id, NULL);
		philos = philos->left_side;
		i++;
	}
	i = 0;
	while (i < table->num_of_philo)
	{
		pthread_mutex_destroy(&philos->left_fork->fork);
		philos = philos->left_side;
		i++;
	}
	debug_philo(table, table->philos);
}

// ./philo [nbr] [die] [eat] [sleep] [eat_time]
int	main(int ac, char *av[])
{
	t_table	table;

	if (ac == 5 || ac == 6)
	{
		// 1. parse input
		parse_input_to_table(&table, av);
		// debug(&table);
		// 2. init struct
		init_philo(&table, &table.philos);
		// 3. start dinner
		start_dinner(&table);
		free_table(&table);
	}
	else
		error_exit("Invalid argument, innit??", &table);
	return (0);
}

/*
考える
フォークを取る
右 左
両方取れたら食事する
フォークを戻す
食事できたら眠る
起きたら考える
死ぬ
誰か死んだら終了


・スレッドに仕事をさせる
哲学者にフォーク2本で食事をさせたい

仕事を分割しそれぞれのスレッドに仕事をさせる
→関数を作成するでも良いし、渡す引数を変えるでも良い

pthread_create()でスレッドを生成する
→引数に分割した仕事を記述した関数を指定する
→コアがこの仕事をしてくれる

同期をすることで他のスレッドの処理を待つことができる

*/