/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 00:04:43 by morip             #+#    #+#             */
/*   Updated: 2026/09/22 14:53:33 by kmoriyam         ###   ########.fr       */
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

void	set_hints(struct addrinfo *hints)
{
	memset(hints, 0, sizeof(struct addrinfo));
	hints->ai_family = AF_INET;
	hints->ai_socktype = SOCK_RAW;
	hints->ai_protocol = IPPROTO_ICMP;
}

void	set_socket(t_tr *tr)
{
	tr->sock_fd = socket(tr->ai->ai_family, tr->ai->ai_socktype, tr->ai->ai_protocol);
	if (tr->sock_fd == -1)
	{
		printf("socket: %s\n", strerror(EINVAL));
		freeaddrinfo(tr->ai);
		exit(2);
	}
}

int	resolve_host(t_tr *tr)
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
	set_socket(tr);
	return (1);
}

int	validate_pakcet_len(char *av[], t_tr *tr)
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

// ./ft_tr <hostname or IP> [packetlen] (extra arg)
int	validate_arg(int ac, char *av[], t_tr *tr)
{
	if (ac == 1)
	{
		print_help();
		return (0);
	}
	tr->hostname = av[1];
	// if (ac > 2)
	// {
	// 	if (validate_pakcet_len(av, tr) == 0)
	// 		return (0);
	// }
	// if (ac > 3)
	// {
	// 	printf("Extra arg `%s' (position 3, argc 3)\n", av[3]);
	// 	freeaddrinfo(tr->ai);
	// 	return (0);
	// }
	return (1);
}

void	init_traceroute(t_tr *tr)
{
	memset(tr, 0, sizeof(t_tr));
	memset(&tr->icmp, 0, sizeof(t_icmp));
	tr->hostname = NULL;
	tr->sock_fd = -1;
}

int	main(int ac, char *av[])
{
	t_tr tr;

	// init vars
	init_traceroute(&tr);

	// validate arg
	if (validate_arg(ac, av, &tr) == 0)
		return (0);
	if (resolve_host(&tr) == 0)
		exit(2);
	write(2, "G\n", 2);
	// set data into packets
	// set_icmp_header();
	// loop send packet, receive packets
	// while (1)
	// {
	// 	char	from[1024];
	// 	ssize_t	from_len;
	// 	sendto();
	// 	recvfrom();
	// }
	// print the ttl, ip, rtt from the packet
	// error handling
	// free addrinfo
	freeaddrinfo(tr.ai);
	return (0);
}