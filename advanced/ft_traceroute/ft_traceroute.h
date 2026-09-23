/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 00:03:49 by morip             #+#    #+#             */
/*   Updated: 2026/09/23 17:26:03 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TRACEROUTE_H
# define FT_TRACEROUTE_H

# include <arpa/inet.h>
# include <netdb.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/errno.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <unistd.h>

# define MAX_HOP_COUNT 30
# define TIMEOUT 30

typedef struct s_icmp
{
	uint8_t			type;
	uint8_t			code;
	uint16_t		checksum;
	uint16_t		id;
	uint16_t		sequence;
	char			data[52];
} __attribute__((packed)) t_icmp;

typedef struct s_tr
{
	t_icmp			icmp;
	struct addrinfo	*ai;
	struct sockaddr_in	sock_in;
	char			*hostname;
	int				sock_fd;
	size_t			max_ttl;
}					t_tr;

void	set_icmp_header(t_tr *tr);

int	resolve_host(t_tr *tr);

u_int16_t	checksum(void *data, size_t len);

void	print_help(void);
void	print_help6(void);
#endif