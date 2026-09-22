/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/18 16:59:38 by kmoriyam          #+#    #+#             */
/*   Updated: 2026/09/22 14:53:16 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

void	print_help2(void);
void	print_help3(void);
void	print_help4(void);
void	print_help5(void);

void	print_help(void)
{
	printf("Usage:\n");
	printf("  traceroute [ -46dFITnreAUDV ] [ -f first_ttl ] [ -g gate,... ] "
		"[ -i device ] [ -m max_ttl ] [ -N squeries ] [ -p port ] [ -t tos ] "
		"[ -l flow_label ] [ -w MAX,HERE,NEAR ] [ -q nqueries ] [ -s src_addr ]"
		" [ -z sendwait ] [ --fwmark=num ] host [ packetlen ]\n");
	printf("Options:\n");
	printf("  -4                          Use IPv4\n");
	printf("  -6                          Use IPv6\n");
	printf("  -d  --debug                 Enable socket level debugging\n");
	printf("  -F  --dont-fragment         Do not fragment packets\n");
	printf("  -f first_ttl  --first=first_ttl\n");
	printf("                              Start from the first_ttl hop "
		"(instead from 1)\n");
	printf("  -g gate,...  --gateway=gate,...\n");
	printf("                              Route packets through the specified "
		"gateway\n");
	printf("                              (maximum 8 for IPv4 and 127 for "
		"IPv6)\n");
	printf("  -I  --icmp                  Use ICMP ECHO for tracerouting\n");
	printf("  -T  --tcp                   Use TCP SYN for tracerouting "
		"(default port is 80)\n");
	printf("  -i device  --interface=device\n");
	printf("                              Specify a network interface to "
		"operate with\n");
	print_help2();
}

void	print_help2(void)
{
	printf("  -m max_ttl  --max-hops=max_ttl\n");
	printf("                              Set the max number of hops "
		"(max TTL to be\n");
	printf("                              reached). Default is 30\n");
	printf("  -N squeries  --sim-queries=squeries\n");
	printf("                              Set the number of probes to be "
		"tried\n");
	printf("                              simultaneously (default is 16)\n");
	printf("  -n                          Do not resolve IP addresses to their "
		"domain names\n");
	printf("  -p port  --port=port        Set the destination port to use. "
		"It is either\n");
	printf("                              initial udp port value for "
		"\"default\" method\n");
	printf("                              (incremented by each probe, "
		"default is 33434), or\n");
	printf("                              initial seq for \"icmp\" "
		"(incremented as well,\n");
	printf("                              default from 1), or "
		"some constant destination\n");
	printf("                              port for other methods "
		"(with default of 80 for\n");
	printf("                              \"tcp\", 53 for \"udp\", etc.)\n");
	print_help3();
}

void	print_help3(void)
{
	printf("  -t tos  --tos=tos           Set the TOS (IPv4 type of "
		"service) or TC (IPv6\n");
	printf("                              traffic class) value for "
		"outgoing packets\n");
	printf("  -l flow_label  --flowlabel=flow_label\n");
	printf("                              Use specified flow_label for "
		"IPv6 packets\n");
	printf("  -w MAX,HERE,NEAR  --wait=MAX,HERE,NEAR\n");
	printf("                              Wait for a probe no more than "
		"HERE (default 3)\n");
	printf("                              times longer than a response "
		"from the same hop,\n");
	printf("                              or no more than NEAR "
		"(default 10) times than some\n");
	printf("                              next hop, or MAX (default 5.0) "
		"seconds (float\n");
	printf("                              point values allowed too)\n");
	printf("  -q nqueries  --queries=nqueries\n");
	printf("                              Set the number of probes "
		"per each hop. Default is\n");
	printf("                              3\n");
	printf("  -r                          Bypass the normal routing "
		"and send directly to a\n");
	printf("                              host on an attached network\n");
	print_help4();
}

void	print_help4(void)
{
	printf("  -s src_addr  --source=src_addr\n");
	printf("                              Use source src_addr for "
		"outgoing packets\n");
	printf("  -z sendwait  --sendwait=sendwait\n");
	printf("                              Minimal time interval between "
		"probes (default 0).\n");
	printf("                              If the value is more than 10, "
		"then it specifies a\n");
	printf("                              number in milliseconds, "
		"else it is a number of\n");
	printf("                              seconds (float point values "
		"allowed too)\n");
	printf("  -e  --extensions            Show ICMP extensions "
		"(if present), including MPLS\n");
	printf("  -A  --as-path-lookups       Perform AS path lookups in "
		"routing registries and\n");
	printf("                              print results directly after "
		"the corresponding\n");
	printf("                              addresses\n");
	printf("  -M name  --module=name      Use specified module "
		"(either builtin or external)\n");
	printf("                              for traceroute operations. "
		"Most methods have\n");
	print_help5();
}

void	print_help5(void)
{
	printf("                              their shortcuts "
		"(`-I' means `-M icmp' etc.)\n");
	printf("  -O OPTS,...  --options=OPTS,...\n");
	printf("                              Use module-specific "
		"option OPTS for the\n");
	printf("                              traceroute module. "
		"Several OPTS allowed,\n");
	printf("                              separated by comma. "
		"If OPTS is \"help\", print info\n");
	printf("                              about available options\n");
	printf("  --sport=num                 Use source port num "
		"for outgoing packets. Implies\n");
	printf("                              `-N 1'\n");
	printf("  --fwmark=num                Set firewall mark "
		"for outgoing packets\n");
	printf("  -U  --udp                   Use UDP to particular port "
		"for tracerouting\n");
	printf("                              (instead of increasing "
		"the port per each probe),\n");
	printf("                              default port is 53\n");
	printf("  -UL                         Use UDPLITE for "
		"tracerouting (default dest port\n");
	printf("                              is 53)\n");
	print_help6();
}
