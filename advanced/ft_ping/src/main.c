#include "../include/ft_ping.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

volatile sig_atomic_t g_running = 1;

void alarm_handler(int sig)
{
	(void)sig;
	// send_ping(&g_ping);
	alarm(1);
}

// signal handler

void	arg_error(void)
{
	const char	msg1[] = "ft_ping: missing host operand\n";
	const char	msg2[] = "Try 'ft_ping --help' or 'ft_ping --usage' for more information.\n";

	write(STDERR_FILENO, msg1, sizeof(msg1));
	write(STDERR_FILENO, msg2, sizeof(msg2));
	exit(EX_USAGE);
}

struct addrinfo	*get_IP_addr(const char *hostname)
{
	struct addrinfo hints, *ai;

	ai = NULL;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET; // IPv4
	hints.ai_socktype = SOCK_RAW; // Bypass Transport Layer
	hints.ai_protocol = IPPROTO_ICMP; // ICMP
	if (getaddrinfo(hostname, NULL, &hints, &ai) != 0) {
		error_getaddrinfo();
		error_func("getaddrinfo() failure");
	}

	return (ai);
}

int	main(int ac, char *av[])
{
	t_ping ping;
	struct addrinfo *addr_info;
	int sock;

	memset(&ping, 0, sizeof(ping));
	ping.icmp_id = getpid() & 0xFFFF;

	// handle option
	parse_args(&ping, ac, av);

	sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (sock < 0)
	{
		error_func("socket() failure");
	}

	// get IP address from hostname
	addr_info = get_IP_addr(ping.hostname);
	if (addr_info == NULL)
	{
		error_func("get_IP_addr() failure");
	}
	memcpy(&ping.dest_addr, addr_info->ai_addr, sizeof(struct sockaddr_in));
	inet_ntop(AF_INET, &ping.dest_addr.sin_addr, ping.ip_str, sizeof(ping.ip_str));
	
	// DEBUG
	printf("%u\n", ping.dest_addr.sin_addr.s_addr);
	printf("host name: %s, host IP: %s\n", ping.hostname, ping.ip_str);
	//

	ping.sockfd = sock;

	printf("PING %s (%s): 56 data bytes\n", ping.hostname, ping.ip_str);
	// create ICMP header

	// send

	// recv
	freeaddrinfo(addr_info);
	close(sock);
	exit(EXIT_SUCCESS);
}