/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/23 17:21:22 by kmoriyam          #+#    #+#             */
/*   Updated: 2026/09/23 17:25:46 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

void	set_hints(struct addrinfo *hints)
{
	memset(hints, 0, sizeof(struct addrinfo));
	hints->ai_family = AF_INET;
	hints->ai_socktype = SOCK_RAW;
	hints->ai_protocol = IPPROTO_ICMP;
}

void	set_socket(t_tr *tr)
{
	int	ttl;

	tr->sock_fd = socket(tr->ai->ai_family, tr->ai->ai_socktype, tr->ai->ai_protocol);
	if (tr->sock_fd == -1)
	{
		printf("socket: %s\n", strerror(EINVAL));
		freeaddrinfo(tr->ai);
		exit(2);
	}
	ttl = 1;
	setsockopt(tr->sock_fd, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl));
}

int	resolve_host(t_tr *tr)
{
	struct addrinfo		hints; // search condition for hostname
	int					error;
	struct sockaddr_in	*addr; // cast send address at last

	set_hints(&hints);
	error = getaddrinfo(tr->hostname, NULL, &hints, &tr->ai);
	if (error)
	{
		printf("%s: %s\n", tr->hostname, gai_strerror(error));
		printf("Cannot handle \"host\" cmdline arg `%s\' on position 1 (argc 1)\n", tr->hostname);
		return (0);
	}
	addr = (struct sockaddr_in *)tr->ai->ai_addr;
	memcpy(&tr->sock_in, addr, sizeof(struct sockaddr_in));
	set_socket(tr);
	return (1);
}
