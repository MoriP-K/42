/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/22 14:52:29 by kmoriyam          #+#    #+#             */
/*   Updated: 2026/09/22 14:54:29 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

void	print_help6(void)
{
	printf("  -D  --dccp                  Use DCCP Request for "
		"tracerouting (default port\n");
	printf("                              is 33434)\n");
	printf("  -P prot  --protocol=prot    Use raw packet of "
		"protocol prot for tracerouting\n");
	printf("  --mtu                       Discover MTU along the "
		"path being traced. Implies\n");
	printf("                              `-F -N 1'\n");
	printf("  --back                      Guess the number of hops "
		"in the backward path and\n");
	printf("                              print if it differs\n");
	printf("  -V  --version               Print version info and exit\n");
	printf("  --help                      Read this help and exit\n");
	printf("\n");
	printf("Arguments:\n");
	printf("+     host          The host to traceroute to\n");
	printf("      packetlen     The full packet length "
		"(default is the length of an IP\n");
	printf("                    header plus 40). Can be ignored "
		"or increased to a minimal\n");
	printf("                    allowed value\n");
}
