/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morip <morip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 00:03:49 by morip             #+#    #+#             */
/*   Updated: 2026/04/18 01:49:49 by morip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TRACEROUTE_H
# define FT_TRACEROUTE_H

# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <arpa/inet.h>
# include <string.h>
# include <sys/errno.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

# define MAX_HOP_COUNT 30
# define TIMEOUT 30

typedef struct	s_icmp
{
	uint8_t		type;
	uint8_t		code;
	uint16_t	checksum;
	uint16_t	id;
	uint16_t	sequence;
	char		data[52];
} __attribute__((packed))	t_icmp;

typedef struct s_traceroute
{
	t_icmp			icmp;
	struct addrinfo	*ai;
	char			*hostname;
	int				sock_fd;
}	t_traceroute;

#endif