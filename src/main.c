/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 20:22:01 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/04/04 22:29:44 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*thread_func(void *arg)
{
	(void)arg;
	printf("func\n");
	return (NULL);
}

int main(int ac, char const *av[])
{
	(void)ac;
	(void)av;
	struct timeval	tv;
	if (gettimeofday(&tv, NULL) == -1)
		perror("gettimeofday");
	printf("timeval: tv_sec = %ld, tv_usec = %ld\n", tv.tv_sec, tv.tv_usec);
	
	pthread_t	thread;
	pthread_attr_t	attr;
	void	*arg = NULL;

	pthread_attr_init(&attr);
	if (pthread_create(&thread, &attr, thread_func, arg) != 0)
		perror("pthread_create");
	printf("thread = %p, attr = %p, arg = %p\n", (void *)&thread, (void *)&attr, arg);
	return (0);
}
