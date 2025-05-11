/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 20:22:01 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/05/11 18:29:57 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

//number of philos ... philos and also forks
//time to die  ... 
//time to ear 
//time to sleep

void	parse_input(t_table *table, char **av)
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
}

t_philo	*find_first_philo_list(t_philo *head, t_table *table)
{
	t_philo	*current;
	t_philo	*first;
	int		i;

	if (!head)
		return (NULL);
	current = head;
	first = current;
	i = 0;
	while (i < table->num_of_philo)
	{
		if (current->id < first->id)
			first = current;
		current = current->left_side;
		if (current == head)
			break ;
		i++;
	}
	return (first);
}

// t_philo	*last_philo_list(t_philo *head, t_table *table)
// {
// 	t_philo	*first;

// 	if (!head)
// 		return (NULL);
// 	first = find_first_philo_list(head, table);
// 	return (first->right_side);
// }

void	add_first_philo(t_philo *new_philo, t_philo *first, t_philo *last)
{
	new_philo->left_side = first;
	new_philo->right_side = last;
	first->left_side = new_philo;
	last->right_side = new_philo;
}

void	add_philo_to_left(t_philo *new_philo, t_philo *prev_philo)
{
	new_philo->right_side = prev_philo;
	new_philo->left_side = prev_philo->left_side;
	prev_philo->left_side->right_side = new_philo;
	prev_philo->left_side = new_philo;
}

void	add_philo_list(t_philo **head, t_philo *new_philo, t_philo *prev_philo, t_table *table)
{
	t_philo	*first;
	t_philo	*last;

	if (!*head)
	{
		*head = new_philo;
		new_philo->right_side = new_philo;
		new_philo->left_side = new_philo;
	}
	else
	{
		first = find_first_philo_list(*head, table);
		last = first->right_side;
		if (!prev_philo)
			add_first_philo(new_philo, first, last);
		else
			add_philo_to_left(new_philo, prev_philo);
	}
}

t_philo	*new_philo_list(t_table *table)
{
	t_philo *new_philo;

	new_philo = ft_malloc(sizeof(t_philo), table);
	new_philo->id = -1;
	new_philo->left_fork = NULL;
	new_philo->right_fork = NULL;
	new_philo->left_side = NULL;
	new_philo->right_side = NULL;
	return (new_philo);
}

void	assign_fork(t_table *table)
{
	t_philo	*tmp;
	t_fork	*next_right_fork;
	int	i;

	tmp = table->philos;
	next_right_fork = NULL;
	i = 0;
	while (i < table->num_of_philo)
	{
		if (i != 0)
			tmp->right_fork = next_right_fork;
		tmp->left_fork = ft_malloc(sizeof(t_fork), table);
		tmp->left_fork->id = i + 1;
		tmp->left_fork->sum = 0;
		next_right_fork = tmp->left_fork;
		// if (i != 0)
		// 	printf("id: %d, left_fork_id: %d, right_fork_id: %d\n", tmp->id, tmp->left_fork->id, tmp->right_fork->id);
		tmp = tmp->left_side;
		i++;
	}
	tmp->right_fork = next_right_fork;
	// printf("id: %d, left_fork_id: %d, right_fork_id: %d\n", tmp->id, tmp->left_fork->id, tmp->right_fork->id);
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

void	debug_philo(t_table *table, t_philo	*philo)
{
	int	i;

	i = 0;
	while (i < table->num_of_philo)
	{
		printf("id: %d\n", philo->id);
		philo = philo->left_side;
		i++;
	}
	printf("sum: %d\n", philo->left_fork->sum);
}

void	*philosopher_lifecycle(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->left_fork->fork);
	pthread_mutex_lock(&philo->right_fork->fork);
	philo->sum++;
	pthread_mutex_unlock(&philo->fork);
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
		printf("index: %d\n", i);
	}
	i = 0;
	while (i < table->num_of_philo)
	{
		pthread_join(philos->p_id, NULL);
		philos = philos->left_side;
		i++;
	}
	debug_philo(table, table->philos);
}

// ./philo [nbr] [die] [eat] [sleep] [eat_time]
int main(int ac, char *av[])
{
	t_table	table;

	if (ac == 5 || ac == 6)
	{
		// 1. parse input
		parse_input(&table, av);
		// debug(&table);
		// 2. init struct
		init_philo(&table, &table.philos);
		// 3. start dinner 
		start_dinner(&table);
		free_table(&table);
	}
	else
		error_exit("Invalid argument, innit??", &table);
	return 0;
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