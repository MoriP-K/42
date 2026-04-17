/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morip <morip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 00:04:43 by morip             #+#    #+#             */
/*   Updated: 2026/04/18 02:09:18 by morip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

/*
# traceroute  asdf
asdf: Name or service not known
Cannot handle "host" cmdline arg `asdf' on position 1 (argc 1)
exit 2

# traceroute google.com asdfas
Cannot handle "packetlen" cmdline arg `asdfas' on position 2 (argc 2)
exit 2

# traceroute google.com sfff asdf
Extra arg `asdf' (position 3, argc 3)
exit 2

success? 130
*/

void	print_help(void)
{
	sleep(1);
}

void	set_hints(struct addrinfo *hints)
{
	memset(hints, 0, sizeof(struct addrinfo));
	hints->ai_family = AF_INET;
	hints->ai_socktype = SOCK_RAW;
	hints->ai_protocol = IPPROTO_ICMP;
}

int	resolve_host(t_traceroute *tr)
{
	struct addrinfo	hints;
	int				error;

	set_hints(&hints);
	error = getaddrinfo(tr->hostname, NULL, &hints, &tr->ai);
	if (error)
	{
		printf("%s: %s\n", tr->hostname, gai_strerror(error));
		printf("Cannot handle \"host\" cmdline arg `%s\' on position 1 (argc 1)\n", tr->hostname);
		return (0);
	}
	return (1);
}

void	set_socket(t_traceroute *tr)
{
	tr->sock_fd = socket(tr->ai->ai_family, tr->ai->ai_socktype, tr->ai->ai_protocol);
	if (tr->sock_fd == -1)
	{
		printf("socket: %s\n", strerror(EINVAL));
		freeaddrinfo(tr->ai);
		exit(2);
	}
}
int	validate_pakcet_len(char *av[], t_traceroute *tr)
{
	int packet_len;

	packet_len = atoi(av[2]); // TODO
	printf("%d\n", packet_len);
	if (packet_len <= 0)
	{
		printf("Cannot handle \"packetlen\" cmdline arg \
			`%s\' on position 2 (argc 2)\n", av[2]);
		freeaddrinfo(tr->ai);
		return (0);
	}
	return (1);
}

// ./ft_traceroute <hostname or IP> [packetlen] (extra arg)
int	validate_arg(int ac, char *av[], t_traceroute *tr)
{
	if (ac == 1)
		print_help();
	else if (ac > 1)
	{
		tr->hostname = av[1];
		if (resolve_host(tr) == 0)
			return (0);
		if (ac > 2)
		{
			if (validate_pakcet_len(av, tr) == 0)
				return (0);
		}
		if (ac > 3)
		{
			printf("Extra arg `%s' (position 3, argc 3)\n", av[3]);
			freeaddrinfo(tr->ai);
			return (0);
		}
		set_socket(tr);
	}
	return (1);
}

void	init_vars(t_traceroute *tr)
{
	memset(tr, 0, sizeof(t_traceroute));
	memset(&tr->icmp, 0, sizeof(t_icmp));
	tr->hostname = NULL;
	tr->sock_fd = -1;
}

int	main(int ac, char *av[])
{
	t_traceroute tr;

	// init vars
	init_vars(&tr);

	// validate arg
	if (validate_arg(ac, av, &tr) == 0)
	{
		exit(2);
	}
	// set data into packets
	set_icmp_header();
	// loop send packet, receive packets
	while (1)
	{
		char	from[1024];
		ssize_t	from_len;
		sendto();
		recvfrom();
	}
	// print the ttl, ip, rtt from the packet
	// error handling
	// free addrinfo
	freeaddrinfo(tr.ai);
	return (0);
}