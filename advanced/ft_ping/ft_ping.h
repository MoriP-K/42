/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 17:52:58 by kmoriyam          #+#    #+#             */
/*   Updated: 2026/08/29 21:32:16 by kmoriyam         ###   ########.fr       */
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
# include <getopt.h>

extern volatile sig_atomic_t	g_intr;

typedef struct s_ip_header
{
	uint8_t		ver_ihl;
	uint8_t 	tos;
	uint16_t	total_length;
	uint16_t	id;
	uint16_t	flag_fragment;
	uint8_t		ttl;
	uint8_t		protocol;
	u_int16_t	header_checksum;
	uint32_t	src_address;
	uint32_t	dst_address;
}	t_ip_header;

typedef struct s_icmp
{
	uint8_t		type;
	uint8_t		code;
	uint16_t	checksum;
	uint16_t	id;
	uint16_t	sequence;
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
	struct sockaddr_in	sock_in;
	int					sock_fd;
	int					opt;
	int					verbose;
}	t_ping;

int			receive_packet(t_ping *ping);
void		handle_icmp_error(t_ping *ping, t_ip_header ip_header, t_icmp *error_packet);

void		set_timeout(int sock_fd, struct addrinfo *ai);
int			resolve_host(t_ping *ping);

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