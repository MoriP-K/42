/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morip <morip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 16:19:34 by morip             #+#    #+#             */
/*   Updated: 2026/04/15 01:00:39 by morip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PING_H
# define FT_PING_H

# include <sys/socket.h>
# include <sys/types.h>
# include <sys/time.h>
# include <netdb.h>
# include <sys/errno.h>
# include <stdio.h>
# include <string.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <math.h>

extern volatile sig_atomic_t	g_intr;

typedef struct s_icmp
{
	uint8_t		type;
	uint8_t		code;
	uint16_t	checksum;
	uint16_t	id;
	uint16_t	sequence;
	// uint32_t	data;
	char		data[56];
} __attribute__((packed))	t_icmp;

typedef struct s_res
{
	struct sockaddr_in	from;
	socklen_t			from_len;
	char				buf[1024];
}	t_res;

typedef struct s_stat
{
	struct timeval	start;
	struct timeval	end;
	double			max;
	double			min;
	double			avg;
	double			m2;
	double			stddev;
	double			total;
	unsigned char	ttl;
	double			rtt;
	double			time;
	size_t			sequence;
	size_t			received;
	size_t			count;
}	t_stat;

typedef struct s_ping
{
	t_icmp				packet;
	t_stat				stat;
	t_res				res;
	char				*hostname;
	char				*ip;
	struct addrinfo		*ai;
	struct addrinfo		hints;
	struct sockaddr_in	sock_in;
	int					sock_fd;
	int					opt;
	int					verbose;
}	t_ping;

int			receive_packet(t_ping *ping);
void		handle_icmp_error(t_ping *ping, t_icmp *error_packet);

int			set_socket(int *sock_fd);
void		set_timeout(int sock_fd, struct addrinfo *ai);

u_int16_t	checksum(void *data, size_t len);
void		update_stat(t_stat *stat, double latest_time, \
				size_t count, char *buf);
void		signal_handler(int signum);
void		throw_error(const char *func_name, struct addrinfo *ai);

void		print_reply_status(t_ping *ping);
void		print_target(t_ping *ping);
void		print_result(t_stat stat, char *hostname, struct addrinfo *ai);

void		print_usage(void);
void		print_usage2(void);
void		print_usage3(void);

#endif