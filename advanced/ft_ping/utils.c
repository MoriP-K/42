/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morip <morip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 00:35:10 by morip             #+#    #+#             */
/*   Updated: 2026/04/15 00:54:09 by morip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

u_int16_t	checksum(void *data, size_t len)
{
	u_int32_t	sum;
	u_int16_t	*ptr;

	sum = 0;
	ptr = (u_int16_t *)data;
	while (len > 1)
	{
		sum += *ptr++;
		len -= 2;
	}
	if (len == 1)
		sum += *(u_int8_t *)ptr << 8;
	while (sum >> 16)
		sum = (sum >> 16) + (sum & 0xFFFF);
	return ((u_int16_t) ~ sum);
}

void	update_stat(t_stat *stat, double latest_time, size_t count, char *buf)
{
	double	old_avg;
	double	variance;

	old_avg = stat->avg;
	stat->avg += (latest_time - old_avg) / count;
	stat->m2 += (latest_time - old_avg) * (latest_time - stat->avg);
	variance = stat->m2 / count;
	stat->stddev = sqrt(variance);
	stat->ttl = (unsigned char)buf[8];
	if (stat->min == 0 && stat->max == 0)
	{
		stat->min = latest_time;
		stat->max = latest_time;
	}
	if (latest_time < stat->min)
		stat->min = latest_time;
	if (stat->max < latest_time)
		stat->max = latest_time;
	stat->total += latest_time;
}

void	signal_handler(int signum)
{
	(void)signum;
	g_intr = 1;
}

void	throw_error(const char *func_name, struct addrinfo *ai)
{
	perror(func_name);
	if (ai)
		freeaddrinfo(ai);
	exit(EXIT_FAILURE);
}
