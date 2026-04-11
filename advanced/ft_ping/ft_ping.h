/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morip <morip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 16:19:34 by morip             #+#    #+#             */
/*   Updated: 2026/04/11 21:52:19 by morip            ###   ########.fr       */
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

volatile sig_atomic_t intr = 0; // for handling signal

typedef struct s_icmp
{
	u_int8_t type;
	u_int8_t code;
	u_int16_t checksum;
	u_int16_t id;
	u_int16_t sequence;
	uint32_t data;
} t_icmp __attribute__((packed));

typedef struct s_stat
{
	struct timeval start;
	struct timeval end;
	double max;
	double min;
	double total;
	double rtt;
	double time;
	size_t count;
	char *hostname;
} t_stat;