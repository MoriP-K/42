/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morip <morip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 16:18:38 by morip             #+#    #+#             */
/*   Updated: 2026/04/14 01:12:11 by morip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h" 

volatile sig_atomic_t	g_intr;

void	arg_error(void)
{
	const char	msg1[] = "ft_ping: missing host operand\n";
	const char	msg2[] = "Try 'ft_ping --help' or \
		'ft_ping --usage' for more information.\n";

	write(STDERR_FILENO, msg1, sizeof(msg1));
	write(STDERR_FILENO, msg2, sizeof(msg2));
	exit(1);
}

void	init_memory(t_ping *ping)
{
	memset(ping, 0, sizeof(t_ping));
	memset(&ping->ai, 0, sizeof(struct addrinfo *));
	memset(&ping->hints, 0, sizeof(struct addrinfo));
	memset(&ping->stat, 0, sizeof(t_stat));
	memset(&ping->packet, 0, sizeof(t_icmp));
	memset(&ping->sock_in, 0, sizeof(struct sockaddr_in));
	memset(&ping->res, 0, sizeof(t_res));
}

void	get_options(int ac, char *av[], t_ping *ping)
{
	while (1)
	{
		ping->opt = getopt(ac, av, "v?");
		if (ping->opt == -1)
			break ;
		if (ping->opt == 'v')
			ping->verbose = 1;
		else if (ping->opt == '?')
			print_usage();
		else
		{
			fprintf(stderr, "Try 'ft_ping --help' or \
				'ft_ping --usage' for more information.\n");
			exit(64);
		}
	}
}

int	set_socket(int *sock_fd)
{
	*sock_fd = socket(AF_INET, SOCK_RAW, 1);
	return (*sock_fd);
}

void	handle_icmp_error(t_ping *ping, t_icmp *error_packet)
{
	t_icmp	*original_icmp;
	char	*from_ip;

	original_icmp = (t_icmp *)(ping->res.buf + 48);
	if (ntohs(original_icmp->id) != (uint16_t)getpid())
		return ;
	from_ip = inet_ntoa(ping->res.from.sin_addr);
	printf("from %s: icmp_seq: %u ", from_ip, ntohs(original_icmp->sequence));
	if (error_packet->type == 11)
		printf("Time to live exceeded\n");
	else if (error_packet->type == 3)
	{
		if (error_packet->code == 0)
			printf("Destination Net Unreachable\n");
		else if (error_packet->code == 1)
			printf("Destination Host Unreachable\n");
		else if (error_packet->code == 3)
			printf("Destination Port Unreachable\n");
		else
			printf("Dest Unreachable, bad code %d\n", error_packet->code);
	}
	else
		printf("ICMP type=%d, code=%d\n", error_packet->type, error_packet->code);
}

int	receive_packet(t_ping *ping)
{
	ssize_t	rec;
	t_icmp	*reply;

	rec = recvfrom(ping->sock_fd, ping->res.buf, sizeof(ping->res.buf), 0, \
		(struct sockaddr *)&ping->res.from, &ping->res.from_len);
	if (g_intr == 1 || (rec < 0 && errno == EINTR))
		print_result(ping->stat, ping->hostname, ping->ai);
	if (rec > 0)
	{
		if (errno == EINTR)
			print_result(ping->stat, ping->hostname, ping->ai);
		reply = (t_icmp *)(ping->res.buf + 20);
		if (reply->type == 0)
		{
			gettimeofday(&ping->stat.end, NULL);
			ping->stat.time = 0;
			ping->stat.time = (double)(ping->stat.end.tv_sec \
				- ping->stat.start.tv_sec) * 1000.0;
			ping->stat.time += (double)(ping->stat.end.tv_usec \
				- ping->stat.start.tv_usec) / 1000.0;
			update_stat(&ping->stat, ping->stat.time, \
				++ping->stat.count, ping->res.buf);
			print_reply_status(ping);
		}
		else
		{
			if (ping->verbose)
				handle_icmp_error(ping, reply);
			return (1);
		}
	}
	return (0);
}

void	throw_error(const char *func_name, struct addrinfo *ai)
{
	perror(func_name);
	if (ai)
		freeaddrinfo(ai);
	exit(EXIT_FAILURE);
}

int	main(int ac, char *av[])
{
	t_ping	ping;
	ssize_t	n;

	if (ac < 1)
		arg_error();
	init_memory(&ping);
	ping.hints.ai_family = AF_INET;
	ping.hints.ai_socktype = SOCK_RAW;
	ping.hints.ai_protocol = IPPROTO_ICMP;
	get_options(ac, av, &ping);
	ping.hostname = av[optind];
	if (getaddrinfo(ping.hostname, NULL, \
		(const struct addrinfo *)&ping.hints, &ping.ai) != 0)
		throw_error("getaddrinfo", ping.ai);
	if (set_socket(&ping.sock_fd) == -1)
		throw_error("socket", ping.ai);
	ping.packet.type = 8;
	ping.packet.code = 0;
	ping.packet.id = htons(getpid() & 0xFFFF);
	ping.sock_in.sin_family = AF_INET;
	ping.sock_in.sin_port = 0;
	print_target(&ping);
	signal(SIGINT, signal_handler);
	set_timeout(ping.sock_fd, ping.ai);
	while (1)
	{
		ping.packet.sequence = htons(ping.stat.sequence++);
		ping.packet.checksum = 0;
		ping.packet.checksum = checksum(&ping.packet, sizeof(ping.packet));
		gettimeofday(&ping.stat.start, NULL);
		n = sendto(ping.sock_fd, &ping.packet, sizeof(ping.packet), 0, \
			(struct sockaddr *)&ping.sock_in, sizeof(ping.sock_in));
		if (n < 0)
		{
			perror("sendto");
			break ;
		}
		ping.res.from_len = sizeof(ping.res.from);
		if (receive_packet(&ping))
			continue ;
		if (g_intr == 1)
			print_result(ping.stat, ping.hostname, ping.ai);
		sleep(1);
	}
}
