/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 00:53:52 by morip             #+#    #+#             */
/*   Updated: 2026/04/18 18:34:32 by kmoriyam         ###   ########.fr       */
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

int	set_socket(int *sock_fd)
{
	*sock_fd = socket(AF_INET, SOCK_RAW, 1);
	return (*sock_fd);
}

void	set_hints(struct addrinfo *hints)
{
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
		fprintf(stderr, "ft_ping: unknown host\n");
		return (0);
	}
	return (1);
}
