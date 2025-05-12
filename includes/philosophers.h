/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 20:20:48 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/05/12 22:08:25 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h> 
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <errno.h>

# include <string.h>

typedef struct s_table	t_table;
typedef struct s_fork	t_fork;
typedef struct s_philo	t_philo;

typedef pthread_mutex_t	t_mtx;

typedef enum e_option
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}	t_option;

typedef struct s_fork
{
	t_mtx	fork;
	int		id;
}			t_fork;

typedef struct s_philo
{
	int					id;
	t_fork				*right_fork;
	t_fork				*left_fork;
	struct s_philo		*right_side;
	struct s_philo		*left_side;
	pthread_t			p_id;
	t_table				*table;
	t_mtx				meal_mtx;
	long				last_meal_time;
	int					meals_eaten;
}				t_philo;

typedef struct s_table
{
	long	num_of_philo;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	nbr_limit_meals;
	t_philo	*philos;
	long	start_time;
	int		simulation_stop;
	t_mtx	print_mtx;
	t_mtx	stop_mtx;
}	t_table;

// utils
void	error_exit(char *s, t_table *table);
void	*ft_malloc(size_t bytes, t_table *table);
int		ft_atoi(char *str, t_table *table);

// free
void	free_table(t_table *table);

// handle

// list
t_philo	*new_philo_list(t_table *table);
void	add_philo_list(t_philo **head, t_philo *new_philo, t_philo *prev_philo, t_table *table);


#endif