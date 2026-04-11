/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morip <morip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 16:18:38 by morip             #+#    #+#             */
/*   Updated: 2026/04/11 21:52:38 by morip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h" 

u_int16_t checksum(void *data, size_t len)
{
	u_int32_t sum;
	u_int16_t *ptr;

	// printf("len: %zu\n", len);
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
	intr = 1;
}

void print_result(t_stat stat, struct addrinfo *ai)
{
	printf("--- %s ft_ping statistics ---\n", stat.hostname);
	printf("round-trip min/avg/max/stddev = %.3f/%.3f/%.3f/test ms\n", stat.min, stat.total / stat.count, stat.max);
	freeaddrinfo(ai);
	exit(1);
}

// initialize vars func

int main(int ac, char *av[])
{
	if (ac < 1)
		arg_error();
	// add: option from args

	// add: getaddrinfo()
	struct addrinfo *ai;
	struct addrinfo hints;

	memset(&ai, 0 , sizeof(struct addrinfo *));
	memset(&hints, 0 , sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_RAW;
	hints.ai_protocol = IPPROTO_ICMP;
	// hints.ai_flags = AI_CANONNAME; // ?

	t_stat stat;

	memset(&stat, 0, sizeof(t_stat));
	stat.hostname = av[1];
	if (getaddrinfo(stat.hostname, NULL, (const struct addrinfo *)&hints, &ai) != 0)
	{
		perror("getaddrinfo");
		return (1);
	}

	int sock_fd = socket(AF_INET, SOCK_RAW, 1);
	if (sock_fd == -1)
	{
		perror("socket");
	}

	t_icmp packet;

	memset(&packet, 0, sizeof(t_icmp));
	packet.type = 8; // Echo Request
	packet.code = 0;
	packet.id = 0;
	packet.sequence = 0;
	packet.data = 0xdeadbeef;
	packet.checksum = checksum(&packet, sizeof(packet));
	// printf("checksum: %x\n", packet.checksum);

	unsigned char *raw = (unsigned char *)&packet;
	// printf("Memory dump (first 4 bytes): %02x %02x %02x %02x\n", raw[0], raw[1], raw[2], raw[3]);

	struct sockaddr_in sock_in;

	memset(&sock_in, 0, sizeof(struct sockaddr_in));
	sock_in.sin_family = AF_INET;
	sock_in.sin_port = 0;

	printf("FT_PING %s (%%s): %%lu data bytes\n", stat.hostname);

	// add signal handle
	signal(SIGINT, signal_handler);
	while (1)
	{
		gettimeofday(&stat.start, NULL);
		ssize_t n = sendto(sock_fd, &packet, sizeof(packet), 0, (struct sockaddr *)&sock_in, sizeof(sock_in));
		if (n < 0)
		{
			perror("sendto");
			printf("errno: %d\n", errno);
			break;
		}
		char buf[1024];
		struct sockaddr_in from;
		socklen_t from_len;
		from_len = sizeof(from);
		ssize_t rec = recvfrom(sock_fd, buf, sizeof(buf), 0, (struct sockaddr *)&from, &from_len);
		if (rec > 0)
		{
			struct t_icmp *reply = (struct t_icmp *)(buf + 20);
			// add: print result
			if (intr == 1)
				print_result(stat, ai);
			// add: Round Trip Time
			stat.rtt = 0;
			gettimeofday(&stat.end, NULL);
			stat.rtt = (double)(stat.end.tv_sec - stat.start.tv_sec) * 1000.0;
			stat.rtt += (double)(stat.end.tv_usec - stat.start.tv_usec) / 1000.0;
			stat.time = stat.rtt;
			if (stat.min == 0 && stat.max == 0)
			{
				stat.min = stat.rtt;
				stat.max = stat.rtt;
			}
			if (stat.rtt < stat.min)
				stat.min = stat.rtt;
			if (stat.max < stat.rtt)
				stat.max = stat.rtt;
			stat.total += stat.rtt;
			stat.count++;
			printf("%lu bytes from %s: icmp_seq=%u ttl=%%u time=%.3f ms\n", sizeof(packet), stat.hostname, stat.count, 123, stat.time);
			// printf("received type: %d, code: %d\n", reply->type, reply->code);
		}
		sleep(1);
	}
}

/* LINUX print ping
root@3df9d4d01fd5:/app# ping google.com
PING google.com (172.217.211.100): 56 data bytes
64 bytes from 172.217.211.100: icmp_seq=0 ttl=110 time=20.887 ms
64 bytes from 172.217.211.100: icmp_seq=1 ttl=110 time=12.624 ms
64 bytes from 172.217.211.100: icmp_seq=2 ttl=110 time=12.370 ms
^C--- google.com ping statistics ---
3 packets transmitted, 3 packets received, 0% packet loss
round-trip min/avg/max/stddev = 12.370/15.294/20.887/3.956 ms
*/