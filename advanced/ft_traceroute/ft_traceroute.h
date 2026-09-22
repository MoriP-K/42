/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 00:03:49 by morip             #+#    #+#             */
/*   Updated: 2026/09/22 14:53:52 by kmoriyam         ###   ########.fr       */
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

typedef struct s_traceroute
{
	t_icmp			icmp;
	struct addrinfo	*ai;
	char			*hostname;
	int				sock_fd;
}					t_tr;

void	print_help(void);
void	print_help6(void);
#endif