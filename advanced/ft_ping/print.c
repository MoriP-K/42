/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 00:35:08 by morip             #+#    #+#             */
/*   Updated: 2026/09/03 18:32:56 by kmoriyam         ###   ########.fr       */
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
		printf(", id 0x%04x = %u", \
			ntohs(ping->packet.id), ntohs(ping->packet.id));
	printf("\n");
}

void	print_reply_status(t_ping *ping, t_icmp *reply)
{
	char	from_ip[INET_ADDRSTRLEN];

	inet_ntop(AF_INET, &(ping->res.from.sin_addr), from_ip, sizeof(from_ip));
	printf("%lu bytes ", sizeof(ping->packet));
	printf("from %s: ", from_ip);
	printf("icmp_seq=%u ttl=%u ", ntohs(reply->sequence), ping->stat.ttl);
	printf("time=%.3f ms\n", ping->stat.time);
}

void	print_header_dump(t_ip_hdr *ip_header, t_icmp *original_icmp)
{
	const uint16_t	*payload;
	char			src_ip[INET_ADDRSTRLEN];
	char			dst_ip[INET_ADDRSTRLEN];
	size_t			i;

	payload = (const uint16_t *)ip_header;
	printf("IP Hdr Dump:\n");
	i = 0;
	while (i < 10)
		printf(" %04x", ntohs(payload[i++]));
	printf("\n");
	printf("Vr HL TOS  Len   ID Flg  off TTL ");
	printf("Pro  cks      Src      Dst     Data\n");
	printf(" %x  %x  %02x %04x %04x   %d %04x  %02d  %02d %04x %s  %s \n",
		ip_header->vhl >> 4, ip_header->vhl & 0x0f, ip_header->tos,
		ntohs(ip_header->total_length), ntohs(ip_header->id),
		ntohs(ip_header->offset) >> 13, ntohs(ip_header->offset) & 0x1fff,
		ip_header->ttl, ip_header->protocol, ntohs(ip_header->sum),
		inet_ntop(AF_INET, &ip_header->src, src_ip, sizeof(src_ip)), \
		inet_ntop(AF_INET, &ip_header->dst, dst_ip, sizeof(dst_ip)));
	printf("ICMP: type %d, code %d, size %ld, id 0x%04x, seq 0x%04x\n",
		original_icmp->type, original_icmp->code, sizeof(t_icmp),
		ntohs(original_icmp->id), ntohs(original_icmp->sequence));
}

void	print_code_error(uint16_t code)
{
	if (code == 0)
		printf("Destination Net Unreachable\n");
	else if (code == 1)
		printf("Destination Host Unreachable\n");
	else if (code == 3)
		printf("Destination Port Unreachable\n");
	else
		printf("Dest Unreachable, bad code %d\n", code);
}
