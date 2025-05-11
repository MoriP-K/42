/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 20:20:48 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/05/11 18:16:45 by kmoriyam         ###   ########.fr       */
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
	int		sum;
}			t_fork;

typedef struct s_philo
{
	int					id;
	t_fork				*right_fork;
	t_fork				*left_fork;
	struct s_philo		*right_side;
	struct s_philo		*left_side;
	pthread_t			p_id;
}				t_philo;

typedef struct s_table
{
	long	num_of_philo;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	nbr_limit_meals;
	t_philo	*philos;
}	t_table;

// utils
void	error_exit(char *s, t_table *table);
void	*ft_malloc(size_t bytes, t_table *table);
int		ft_atoi(char *str, t_table *table);

// free
void	free_table(t_table *table);

// handle

#endif