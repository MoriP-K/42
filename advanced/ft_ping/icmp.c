/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   icmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 00:50:56 by morip             #+#    #+#             */
/*   Updated: 2026/09/03 18:32:17 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	process_reply(t_ping *ping, t_icmp *reply)
{
	gettimeofday(&ping->stat.end, NULL);
	ping->stat.time = 0;
	ping->stat.time = (double)(ping->stat.end.tv_sec - ping->stat.start.tv_sec)
		* 1000.0;
	ping->stat.time += (double)(ping->stat.end.tv_usec
			- ping->stat.start.tv_usec) / 1000.0;
	ping->stat.received++;
	update_stat(&ping->stat, ping->stat.time, ++ping->stat.count,
		ping->res.buf);
	print_reply_status(ping, reply);
}

int	check_reply(t_ping *ping, t_icmp *reply)
{
	if (ntohs(reply->id) == (uint16_t)(getpid() & 0xFFFF))
	{
		process_reply(ping, reply);
		return (1);
	}
	return (0);
}

ssize_t	handle_receive_packet(t_ping *ping)
{
	ssize_t	rec;

	rec = recvfrom(ping->sock_fd, ping->res.buf, sizeof(ping->res.buf), 0,
			(struct sockaddr *)&ping->res.from, &ping->res.from_len);
	if (g_intr == 1 || (rec < 0 && errno == EINTR))
		print_result(ping->stat, ping->hostname, ping->ai);
	return (rec);
}

int	receive_packet(t_ping *ping)
{
	t_ip_hdr	*outer_ip;
	t_icmp		*outer_icmp;
	size_t		outer_ip_len;

	while (1)
	{
		if (handle_receive_packet(ping) < 0)
			break ;
		outer_ip = (t_ip_hdr *)ping->res.buf;
		outer_ip_len = (outer_ip->vhl & 0x0f) * 4;
		outer_icmp = (t_icmp *)(ping->res.buf + outer_ip_len);
		if (outer_icmp->type == 0)
		{
			if (check_reply(ping, outer_icmp))
				return (0);
		}
		else
			handle_icmp_error(ping, outer_ip, outer_icmp);
	}
	return (1);
}

void	handle_icmp_error(t_ping *ping, t_ip_hdr *outer_ip, t_icmp *outer_icmp)
{
	t_ip_hdr	*inner_ip;
	t_icmp		*original_icmp;
	size_t		outer_ip_len;
	size_t		inner_ip_len;
	char		*from_ip;

	inner_ip = (t_ip_hdr *)((char *)outer_icmp + 8);
	outer_ip_len = (outer_ip->vhl & 0x0f) * 4;
	inner_ip_len = (inner_ip->vhl & 0x0f) * 4;
	original_icmp = (t_icmp *)((char *)inner_ip + inner_ip_len);
	if (ntohs(original_icmp->id) != ((uint16_t)getpid() & 0xFFFF))
		return ;
	from_ip = inet_ntoa(ping->res.from.sin_addr);
	printf("%zu bytes from %s: ", ntohs(outer_ip->total_length) - outer_ip_len,
		from_ip);
	if (outer_icmp->type == 11)
	{
		printf("Time to live exceeded\n");
		if (ping->verbose)
			print_header_dump(inner_ip, original_icmp);
	}
	else if (outer_icmp->type == 3)
		print_code_error(outer_icmp->code);
}
