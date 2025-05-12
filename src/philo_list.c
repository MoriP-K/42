/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 20:53:04 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/05/12 21:22:04 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static t_philo	*find_first_philo_list(t_philo *head, t_table *table)
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

static void	add_first_philo(t_philo *new_philo, t_philo *first, t_philo *last)
{
	new_philo->left_side = first;
	new_philo->right_side = last;
	first->left_side = new_philo;
	last->right_side = new_philo;
}

static void	add_philo_to_left(t_philo *new_philo, t_philo *prev_philo)
{
	new_philo->right_side = prev_philo;
	new_philo->left_side = prev_philo->left_side;
	prev_philo->left_side->right_side = new_philo;
	prev_philo->left_side = new_philo;
}

void	add_philo_list(t_philo **head, t_philo *new_philo, t_philo *prev_philo,
		t_table *table)
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
	t_philo	*new_philo;

	new_philo = ft_malloc(sizeof(t_philo), table);
	new_philo->id = -1;
	new_philo->left_fork = NULL;
	new_philo->right_fork = NULL;
	new_philo->left_side = NULL;
	new_philo->right_side = NULL;
	return (new_philo);
}
