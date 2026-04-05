#pragma once

#include <arpa/inet.h>
#include <inttypes.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

typedef struct s_ping
{
	// target
	const char *hostname;
	char ip_str[INET_ADDRSTRLEN];
	struct sockaddr_in dest_addr;

	// socket
	int sockfd;


	// ICMP
	uint16_t icmp_id;
	uint16_t icmp_seq;

	// options
	int verbose;
	// int count;
	// int quiet;
	int help;

	// statics
	int packets_sent;
	int packets_received;
	double rtt_min;
	double rtt_max;
	double rtt_sum;
	double rtt_sum_sq;
} t_ping;

typedef struct s_icmp_header
{
	uint8_t type;
	uint8_t code;
	uint16_t checksum;
	uint16_t id;
	uint16_t sequence;

} t_icmp_header;

typedef struct s_ip_header
{
	uint8_t ihl_version; // 下位4bit = IHL, 上位4bit = version
	uint8_t tos;
	uint16_t total_length;
	uint16_t id;
	uint16_t flag_offset;
	uint8_t ttl;
	uint8_t protocol;
	uint16_t checksum;
	uint32_t src_addr;
	uint32_t dst_addr;
} t_ip_header;
// IHL 

void	arg_error(void);
struct addrinfo	*get_IP_addr(const char *hostname);

int parse_args(t_ping *ping, int ac, char *av[]);
void print_help(void);
void error_func(const char *msg);
void error_getaddrinfo(void);
	

#define PROTO_ICMP 1
#define  EX_USAGE 64
