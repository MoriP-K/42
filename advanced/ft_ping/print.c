/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morip <morip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 00:35:08 by morip             #+#    #+#             */
/*   Updated: 2026/04/15 00:40:18 by morip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	print_result(t_stat stat, char *hostname, struct addrinfo *ai)
{
	double	loss;

	loss = 0;
	if (stat.sequence > 0)
		loss = (1.0 - (double)stat.received / stat.sequence) * 100.0;
	printf("--- %s ft_ping statistics ---\n", hostname);
	printf("%lu packets transmitted, ", stat.sequence);
	printf("%lu packets received, ", stat.received);
	printf("%.0f%% packet loss\n", loss);
	if (stat.received > 0)
		printf("round-trip min/avg/max/stddev = %.3f/%.3f/%.3f/%.3f ms\n", \
			stat.min, stat.total / stat.count, stat.max, stat.stddev);
	freeaddrinfo(ai);
	exit(1);
}

void	print_target(t_ping *ping)
{
	struct sockaddr_in	*sin;

	sin = (struct sockaddr_in *)ping->ai->ai_addr;
	ping->ip = inet_ntoa(sin->sin_addr);
	ping->sock_in.sin_addr = sin->sin_addr;
	printf("FT_PING %s (%s): %lu data bytes", \
		ping->hostname, ping->ip, sizeof(t_icmp) - 8);
	if (ping->verbose)
		printf(" id %#02x = %u", ping->packet.id, ping->packet.id);
	printf("\n");
}

void	print_reply_status(t_ping *ping)
{
	printf("%lu bytes ", sizeof(ping->packet));
	printf("from %s: ", ping->ip);
	printf("icmp_seq=%lu ttl=%u ", ping->stat.received++, ping->stat.ttl);
	printf("time=%.3f ms\n", ping->stat.time);
}
