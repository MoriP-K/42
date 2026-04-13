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

void	set_timeout(int sock_fd, struct addrinfo *ai)
{
	struct timeval	tv;

	tv.tv_sec = 1;
	tv.tv_usec = 0;
	if (setsockopt(sock_fd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) < 0)
	{
		perror("setsockopt");
		freeaddrinfo(ai);
		exit(EXIT_FAILURE);
	}
}

void	signal_handler(int signum)
{
	(void)signum;
	g_intr = 1;
}
