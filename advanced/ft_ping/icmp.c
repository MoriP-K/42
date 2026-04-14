/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   icmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morip <morip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 00:50:56 by morip             #+#    #+#             */
/*   Updated: 2026/04/15 01:48:41 by morip            ###   ########.fr       */
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

	while (1)
	{
		if (handle_receive_packet(ping) == 0)
			break ;
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
			if (ping->verbose)
				handle_icmp_error(ping, reply);
			continue ;
		}
	}
	return (1);
}

void	handle_icmp_error(t_ping *ping, t_icmp *error_packet)
{
	t_icmp	*original_icmp;
	char	*from_ip;

	original_icmp = (t_icmp *)(ping->res.buf + 48);
	if (ntohs(original_icmp->id) != ((uint16_t)getpid() & 0xFFFF))
		return ;
	from_ip = inet_ntoa(ping->res.from.sin_addr);
	printf("from %s: icmp_seq: %u ", from_ip, ntohs(original_icmp->sequence));
	if (error_packet->type == 11)
		printf("Time to live exceeded\n");
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
		printf("ICMP type=%d, code=%d\n", \
			error_packet->type, error_packet->code);
}
