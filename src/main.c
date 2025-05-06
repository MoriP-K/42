/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 20:22:01 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/05/06 21:51:35 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

//number of philos ... philos and also forks
//time to die  ... 
//time to ear 
//time to sleep

void	error_exit(char *s)
{
	printf("%s\n", s);
	exit(EXIT_FAILURE);
}

int	is_space(char c)
{
	return ((9 <= c && c <= 13) || c == 32);
}

int	ft_atoi(char *str)
{
	size_t	i;
	long	num;

	i = 0;
	while(is_space(str[i]))
		i++;
	num = 0;
	return (num);
}

void	parse_input(t_table *table, char **av)
{
	table->philo_nbr = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
}

int main(int ac, char *av[])
{
	t_table	table;

	if (ac == 5 || ac == 6)
	{
		// correct input
		// 1. parse input
		parse_input(&table, av);
		// 2. init struct
		// 3. start dinner 
	}
	else
		error_exit("Invalid arguments\n");
	return 0;
}



// static volatile int	glob = 0;
// static	pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

// void	*thread_func(void *arg)
// {
// 	int	loop = *((int *)arg);
// 	int	loc, j, s;

// 	for (j = 0; j < loop; j++)
// 	{
// 		s = pthread_mutex_lock(&mtx);
// 		if (s != 0)
// 			printf("pthread_mutex_lock\n");
// 		loc = glob;
// 		loc++;
// 		glob = loc;
// 		s = pthread_mutex_unlock(&mtx);
// 		if (s != 0)
// 			printf("pthred_mutex_lock\n");
// 	}
// 	return (NULL);
// }

// int main(int ac, char const *av[])
// {
// 	(void)ac;
// 	(void)av;

// 	pthread_t t1, t2;
// 	int		loop, s;

// 	loop = (ac > 1) ? atoi(av[1]) : 10000000;
// 	s = pthread_create(&t1, NULL, thread_func, &loop);
// 	if (s != 0)
// 		printf("pthread_create1\n");
// 	s = pthread_create(&t2, NULL, thread_func, &loop);
// 	if (s != 0)
// 		printf("pthread_create2\n");
// 	s = pthread_join(t1, NULL);
// 	if (s != 0)
// 		printf("pthread_join1\n");
// 	s = pthread_join(t2, NULL);
// 	if (s != 0)
// 		printf("pthread_join2\n");
// 	printf("glob = %d\n", glob);
// 	return (0);
// }

// typedef struct s_mut
// {
// 	pthread_mutex_t *mutex;
// 	int *cnt;
// }	t_mut;


// void	*f(void *p)
// {
// 	t_mut	*t;

// 	t = p;
// 	for (int i = 0; i < 10000; i++)
// 	{
// 		pthread_mutex_lock(t->mutex);
// 		++*t->cnt;
// 		pthread_mutex_unlock(t->mutex);
// 	}
// 	return (NULL);
// }

// int	main()
// {
// 	int cnt = 0;
// 	pthread_t t1, t2;
// 	pthread_mutex_t mutex;

// 	pthread_mutex_init(&mutex, NULL);
// 	t_mut t;
// 	t.mutex = &mutex;
// 	t.cnt = &cnt;
// 	pthread_create(&t1, NULL, &f, &t);
// 	pthread_create(&t2, NULL, &f, &t);
// 	pthread_join(t1, NULL);
// 	pthread_join(t2, NULL);
// 	printf("t.cnt = %d\n", *t.cnt);
// }