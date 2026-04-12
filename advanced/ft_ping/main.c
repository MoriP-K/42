/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morip <morip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 16:18:38 by morip             #+#    #+#             */
/*   Updated: 2026/04/12 17:07:05 by morip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h" 

u_int16_t checksum(void *data, size_t len)
{
	u_int32_t sum;
	u_int16_t *ptr;

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
	return (u_int16_t)~sum;
}

void arg_error(void)
{
	const char msg1[] = "ft_ping: missing host operand\n";
	const char msg2[] = "Try 'ft_ping --help' or 'ft_ping --usage' for more information.\n";

	write(STDERR_FILENO, msg1, sizeof(msg1));
	write(STDERR_FILENO, msg2, sizeof(msg2));
	exit(1);
}

void signal_handler(int signum)
{
	(void)signum;
	intr = 1;
}

void print_result(t_stat stat, struct addrinfo *ai)
{
	double loss;

	loss = 0;
	if (stat.sequence > 0)
		loss = (1.0 - (double)stat.received / stat.sequence) * 100.0;
	printf("--- %s ft_ping statistics ---\n", stat.hostname);
	printf("%lu packets transmitted, %lu packets received, %.0f%% packet loss\n", stat.sequence, stat.received, loss);
	printf("round-trip min/avg/max/stddev = %.3f/%.3f/%.3f/%.3f ms\n", stat.min, stat.total / stat.count, stat.max, stat.stddev);
	freeaddrinfo(ai);
	exit(1);
}

void init_memory(t_ping *ping)
{
	memset(ping, 0, sizeof(t_ping));
	memset(&ping->ai, 0 , sizeof(struct addrinfo *));
	memset(&ping->hints, 0 , sizeof(struct addrinfo));
	memset(&ping->stat, 0, sizeof(t_stat));
	memset(&ping->packet, 0, sizeof(t_icmp));
	memset(&ping->sock_in, 0, sizeof(struct sockaddr_in));
	memset(&ping->res, 0, sizeof(t_res));
}

void update_stat(t_stat *stat, double latest_time, size_t count, char *buf)
{
	double old_avg;
	double variance;

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

int main(int ac, char *av[])
{
	t_ping ping;
	ssize_t n;
	ssize_t rec;
	t_icmp *reply;

	if (ac < 1)
		arg_error();
	// add: option from args

	init_memory(&ping);

	ping.hints.ai_family = AF_INET;
	ping.hints.ai_socktype = SOCK_RAW;
	ping.hints.ai_protocol = IPPROTO_ICMP;
	// hints.ai_flags = AI_CANONNAME; // ?

	ping.stat.hostname = av[1];
	if (getaddrinfo(ping.stat.hostname, NULL, (const struct addrinfo *)&ping.hints, &ping.ai) != 0)
	{
		perror("getaddrinfo");
		return (1);
	}

	ping.sock_fd = socket(AF_INET, SOCK_RAW, 1);
	if (ping.sock_fd == -1)
	{
		perror("socket");
	}

	ping.packet.type = 8; // Echo Request
	ping.packet.code = 0;
	ping.packet.id = 0;

	ping.sock_in.sin_family = AF_INET;
	ping.sock_in.sin_port = 0;

	struct sockaddr_in *sin = (struct sockaddr_in *)ping.ai->ai_addr;
	char *ip = inet_ntoa(sin->sin_addr);
	printf("FT_PING %s (%s): %lu data bytes\n", ping.stat.hostname, ip, sizeof(t_icmp));
	ping.sock_in.sin_addr = sin->sin_addr;

	signal(SIGINT, signal_handler);
	struct timeval tv;
	tv.tv_sec = 1;
	tv.tv_usec = 0;
	setsockopt(ping.sock_fd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
	while (1)
	{
		ping.packet.sequence = htons(ping.stat.sequence++);
		ping.packet.checksum = 0;
		ping.packet.checksum = checksum(&ping.packet, sizeof(ping.packet));
		gettimeofday(&ping.stat.start, NULL);
		n = sendto(ping.sock_fd, &ping.packet, sizeof(ping.packet), 0, (struct sockaddr *)&ping.sock_in, sizeof(ping.sock_in));
		if (n < 0)
		{
			perror("sendto");
			break;
		}
		ping.res.from_len = sizeof(ping.res.from);
		rec = recvfrom(ping.sock_fd, ping.res.buf, sizeof(ping.res.buf), 0, (struct sockaddr *)&ping.res.from, &ping.res.from_len);
		if (intr == 1 || (rec < 0 && errno == EINTR))\
			print_result(ping.stat, ping.ai);
		if (rec > 0)
		{
			if (errno == EINTR)
				print_result(ping.stat, ping.ai);
			reply = (t_icmp *)(ping.res.buf + 20);
			if (reply->type != 0)
				continue;
			gettimeofday(&ping.stat.end, NULL);
			ping.stat.time = 0;
			ping.stat.time = (double)(ping.stat.end.tv_sec - ping.stat.start.tv_sec) * 1000.0;
			ping.stat.time += (double)(ping.stat.end.tv_usec - ping.stat.start.tv_usec) / 1000.0;
			update_stat(&ping.stat, ping.stat.time, ++ping.stat.count, ping.res.buf);
			printf("%lu bytes from %s: icmp_seq=%lu ttl=%u time=%.3f ms\n", sizeof(ping.packet), ping.stat.hostname, ping.stat.received++, ping.stat.ttl, ping.stat.time);
		}
		if (intr == 1)
			print_result(ping.stat, ping.ai);
		sleep(1);
	}
}
