/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 16:18:38 by morip             #+#    #+#             */
/*   Updated: 2026/04/18 18:30:43 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h" 

volatile sig_atomic_t	g_intr;

void	arg_error(void)
{
	const char	msg1[] = "ft_ping: missing host operand\n";
	const char	msg2[] = "Try 'ft_ping --help' or ";
	const char	msg3[] = "'ft_ping --usage' for more information.\n";

	write(STDERR_FILENO, msg1, sizeof(msg1));
	write(STDERR_FILENO, msg2, sizeof(msg2));
	write(STDERR_FILENO, msg3, sizeof(msg3));
	exit(1);
}

void	init_memory(t_ping *ping)
{
	memset(ping, 0, sizeof(t_ping));
	memset(&ping->ai, 0, sizeof(struct addrinfo *));
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
			fprintf(stderr, "Try 'ft_ping --help' or ");
			fprintf(stderr, "'ft_ping --usage' for more information.\n");
			exit(64);
		}
	}
}

void	run(t_ping *ping)
{
	ssize_t	n;

	while (1)
	{
		if (g_intr == 1)
			print_result(ping->stat, ping->hostname, ping->ai);
		ping->packet.sequence = htons(ping->stat.sequence++);
		ping->packet.checksum = 0;
		ping->packet.checksum = checksum(&ping->packet, sizeof(ping->packet));
		gettimeofday(&ping->stat.start, NULL);
		n = sendto(ping->sock_fd, &ping->packet, sizeof(ping->packet), 0, \
			(struct sockaddr *)&ping->sock_in, sizeof(ping->sock_in));
		if (n < 0)
			throw_error("sentdo", ping->ai);
		ping->res.from_len = sizeof(ping->res.from);
		receive_packet(ping);
		if (g_intr == 1)
			print_result(ping->stat, ping->hostname, ping->ai);
		sleep(1);
	}
}

// void	set_ttl_one(int sock_fd)
// {
// 	int	ttl;

// 	ttl = 1;
// 	if (setsockopt(sock_fd, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl)) < 0)
// 		perror("setsockopt IP_TTL");
// }

int	main(int ac, char *av[])
{
	t_ping	ping;

	if (ac < 2)
		arg_error();
	init_memory(&ping);
	get_options(ac, av, &ping);
	ping.hostname = av[optind];
	if (resolve_host(&ping) == 0)
		exit (2);
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
	run(&ping);
}
