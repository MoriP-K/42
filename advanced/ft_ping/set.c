/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morip <morip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 00:53:52 by morip             #+#    #+#             */
/*   Updated: 2026/08/27 15:06:32 by morip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	set_timeout(int sock_fd, struct addrinfo *ai)
{
	struct timeval	tv;

	tv.tv_sec = 1;
	tv.tv_usec = 0;
	if (setsockopt(sock_fd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) < 0)
		throw_error("setsockopt", ai);
}

void	set_hints(struct addrinfo *hints)
{
	memset(hints, 0, sizeof(struct addrinfo));
	hints->ai_family = AF_INET;
	hints->ai_socktype = SOCK_RAW;
	hints->ai_protocol = IPPROTO_ICMP;
}

int	resolve_host(t_ping *ping)
{
	struct addrinfo	hints;
	int				error;

	set_hints(&hints);
	error = getaddrinfo(ping->hostname, NULL, &hints, &ping->ai);
	if (error)
	{
		fprintf(stderr, "ft_ping: %s\n", gai_strerror(error));
		return (0);
	}
	return (1);
}
