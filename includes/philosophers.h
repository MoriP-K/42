/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 20:20:48 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/05/14 22:10:35 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_table	t_table;
typedef struct s_fork	t_fork;
typedef struct s_philo	t_philo;

typedef pthread_mutex_t	t_mtx;

typedef struct s_fork
{
	t_mtx				fork;
	int					id;
}						t_fork;

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
}						t_philo;

typedef struct s_table
{
	long				num_of_philo;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				nbr_limit_meals;
	t_philo				*philos;
	long				start_time;
	int					simulation_stop;
	t_mtx				print_mtx;
	t_mtx				stop_mtx;
}						t_table;

// init
void					init_table(t_table *table);
void					init_philo(t_table *table, t_philo **head);
void					init_mtx_philos(t_table *table);

//
void					*philo_lifecycle(void *arg);
void					monitor_philos_status(t_table *table);

// utils
void					error_exit(char *s, t_table *table);
void					*ft_malloc(size_t bytes, t_table *table);
int						ft_atoi(char *str);
long					now(void);
void					print_status(t_philo *philo, char *text);
int						is_simulation_stopped(t_table *table);

// free
void					free_table(t_table *table);
void					free_philos(t_philo **philo, t_table *table);

// list
t_philo					*new_philo_list(t_table *table);
void					add_philo_list(t_philo **head, t_philo *new_philo,
							t_philo *prev_philo, t_table *table);

#endif