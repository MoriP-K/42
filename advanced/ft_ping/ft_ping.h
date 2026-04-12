/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morip <morip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 16:19:34 by morip             #+#    #+#             */
/*   Updated: 2026/04/12 15:24:58 by morip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#include <netdb.h>
#include <sys/errno.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <math.h>

volatile sig_atomic_t intr = 0; // for handling signal

typedef struct s_icmp
{
	uint8_t type;
	uint8_t code;
	uint16_t checksum;
	uint16_t id;
	uint16_t sequence;
	// uint32_t data;
	char data[56];
} __attribute__((packed)) t_icmp;

typedef struct s_res
{
	char buf[1024];
	struct sockaddr_in from;
	socklen_t from_len;
} t_res;

typedef struct s_stat
{
	struct timeval start;
	struct timeval end;
	double max;
	double min;
	double avg;
	double m2;
	double stddev;
	double total;
	unsigned char ttl;
	double rtt;
	double time;
	size_t sequence;
	size_t received;
	size_t count;
	char *hostname;
} t_stat;

typedef struct s_ping
{
	t_icmp packet;
	t_stat stat;
	t_res res;
	struct addrinfo *ai;
	struct addrinfo hints;
	struct sockaddr_in sock_in;
	int sock_fd;
} t_ping;
