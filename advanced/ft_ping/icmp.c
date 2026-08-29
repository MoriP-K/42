/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   icmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 00:50:56 by morip             #+#    #+#             */
/*   Updated: 2026/08/29 21:53:32 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	process_reply(t_ping *ping)
{
	gettimeofday(&ping->stat.end, NULL);
	ping->stat.time = 0;
	ping->stat.time = (double)(ping->stat.end.tv_sec \
		- ping->stat.start.tv_sec) * 1000.0;
	ping->stat.time += (double)(ping->stat.end.tv_usec \
		- ping->stat.start.tv_usec) / 1000.0;
	update_stat(&ping->stat, ping->stat.time, \
		++ping->stat.count, ping->res.buf);
	print_reply_status(ping);
}

int	check_reply(t_ping *ping, t_icmp *reply)
{
	if (ntohs(reply->id) == (uint16_t)(getpid() & 0xFFFF))
	{
		process_reply(ping);
		return (1);
	}
	return (0);
}

int	handle_receive_packet(t_ping *ping)
{
	ssize_t	rec;

	rec = recvfrom(ping->sock_fd, ping->res.buf, sizeof(ping->res.buf), 0, \
		(struct sockaddr *)&ping->res.from, &ping->res.from_len);
	if (g_intr == 1 || (rec < 0 && errno == EINTR))
		print_result(ping->stat, ping->hostname, ping->ai);
	if (rec < 0)
		return (0);
	return (1);
}

int	receive_packet(t_ping *ping)
{
	t_icmp	*reply;
	t_ip_header	*ip_header;

	while (1)
	{
		if (handle_receive_packet(ping) == 0)
			break ;
		ip_header = (t_ip_header *)ping->res.buf;
		reply = (t_icmp *)(ping->res.buf + 20);
		if (errno == EINTR)
			print_result(ping->stat, ping->hostname, ping->ai);
		if (reply->type == 0)
		{
			if (check_reply(ping, reply))
				return (0);
			continue ;
		}
		else
		{
			// printf("type: %d\n", reply->type);
			// if (ping->verbose)
				handle_icmp_error(ping, *ip_header, reply);
			continue ;
		}
	}
	return (1);
}

void print_header_dump(t_icmp packet, t_ip_header ip_header, t_ping ping)
{
	struct in_addr src_header;
	struct in_addr dst_header;

	src_header.s_addr = ip_header.src_address;
	dst_header.s_addr = ip_header.dst_address;
	(void)ping;
	printf("IP Hdr Dump:\n");
	printf(" %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x\n",\
		ip_header.ver_ihl, ip_header.tos, ip_header.total_length,\
		ip_header.id, ip_header.flag_fragment,\
		ip_header.ttl, ip_header.protocol, ip_header.header_checksum,\
		ip_header.src_address, ip_header.dst_address);
	printf("Vr HL TOS  Len   ID Flg  off TTL Pro  cks      Src    Dst    Data\n");
	printf(" %x  %x  %02x %04x %04x   %d %04x  %02d  %02d %04x %s  %s \n",\
		ip_header.ver_ihl << 8, ip_header.ver_ihl, ip_header.tos, ip_header.total_length,\
		ip_header.id, ip_header.flag_fragment, ip_header.flag_fragment,\
		ip_header.ttl, ip_header.protocol, ip_header.header_checksum,\
		inet_ntoa(src_header), inet_ntoa(dst_header));
	printf("ICMP: type %d, code %d, size %ld, id %#04x, seq %#04x\n",\
		packet.type, packet.code, sizeof(t_icmp), packet.id, packet.sequence++);
}

// $ ping --ttl 1 -v google.com 
// PING google.com (142.251.23.100): 56 data bytes, id 0x154e = 5454 
// 36 bytes from _gateway (10.0.2.2): Time to live exceeded 
// IP Hdr Dump:
//  4500 0054 be79 4000 0101 08c2 0a00 020f 8efb 1764  
// Vr HL TOS  Len   ID Flg  off TTL Pro  cks      Src    Dst    Data  
//  4  5  00 0054 be79   2 0000  01  01 08c2 10.0.2.15  142.251.23.100  
// ICMP: type 8, code 0, size 64, id 0x154e, seq 0x0000

void	handle_icmp_error(t_ping *ping, t_ip_header ip_header, t_icmp *error_packet)
{
	t_icmp	*original_icmp;
	char	*from_ip;

	original_icmp = (t_icmp *)(ping->res.buf + 48);
	if (ntohs(original_icmp->id) != ((uint16_t)getpid() & 0xFFFF))
		return ;	
	from_ip = inet_ntoa(ping->res.from.sin_addr);
	printf("%ld bytes from %s: ", sizeof(t_icmp) - 28, from_ip);
	if (error_packet->type == 11)
	{
		printf("Time to live exceeded\n");
		if (ping->verbose)
			print_header_dump(*error_packet, ip_header, *ping);
	}
	else if (error_packet->type == 3)
	{
		if (error_packet->code == 0)
			printf("Destination Net Unreachable\n");
		else if (error_packet->code == 1)
			printf("Destination Host Unreachable\n");
		else if (error_packet->code == 3)
			printf("Destination Port Unreachable\n");
		else
			printf("Dest Unreachable, bad code %d\n", error_packet->code);
	}
	else
		printf("ICMP type %d, code %d, size %ld, id %#04x, seq %#04x\n", \
			error_packet->type, error_packet->code, sizeof(error_packet->data), error_packet->id, error_packet->sequence);
}
