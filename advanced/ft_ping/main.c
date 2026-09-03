/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 16:18:38 by morip             #+#    #+#             */
/*   Updated: 2026/09/03 18:28:24 by kmoriyam         ###   ########.fr       */
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
			throw_error("sendto", ping->ai);
		ping->res.from_len = sizeof(ping->res.from);
		receive_packet(ping);
		if (g_intr == 1)
			print_result(ping->stat, ping->hostname, ping->ai);
		sleep(1);
	}
}

void	set_ttl_one(int sock_fd)
{
	int	ttl;

	ttl = 1;
	if (setsockopt(sock_fd, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl)) < 0)
		perror("setsockopt IP_TTL");
}

int	main(int ac, char *av[])
{
	t_ping	ping;

	if (ac < 2)
		arg_error();
	memset(&ping, 0, sizeof(t_ping));
	get_options(ac, av, &ping);
	if (optind >= ac)
		arg_error();
	ping.hostname = av[optind];
	set_ping_defaults(&ping);
	if (resolve_host(&ping) == 0)
		exit (2);
	ping.sock_fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (ping.sock_fd == -1)
		throw_error("socket", ping.ai);
	set_ttl_one(ping.sock_fd);
	print_target(&ping);
	signal(SIGINT, signal_handler);
	set_timeout(ping.sock_fd, ping.ai);
	run(&ping);
}
