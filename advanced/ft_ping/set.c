/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morip <morip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 00:53:52 by morip             #+#    #+#             */
/*   Updated: 2026/04/15 01:02:53 by morip            ###   ########.fr       */
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
