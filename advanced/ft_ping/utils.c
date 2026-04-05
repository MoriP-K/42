#include "ft_ping.h"
#include <stdio.h>
#include <stdlib.h>

/*
Usage: inet-ping [OPTION...] HOST ...
Send ICMP ECHO_REQUEST packets to network hosts.

 Options controlling ICMP request types:
      --address              send ICMP_ADDRESS packets (root only)
      --echo                 send ICMP_ECHO packets (default)
      --mask                 same as --address
      --timestamp            send ICMP_TIMESTAMP packets
  -t, --type=TYPE            send TYPE packets

 Options valid for all request types:

  -c, --count=NUMBER         stop after sending NUMBER packets
  -d, --debug                set the SO_DEBUG option
  -i, --interval=NUMBER      wait NUMBER seconds between sending each packet
  -n, --numeric              do not resolve host addresses
  -r, --ignore-routing       send directly to a host on an attached network
      --ttl=N                specify N as time-to-live
  -T, --tos=NUM              set type of service (TOS) to NUM
  -v, --verbose              verbose output
  -w, --timeout=N            stop after N seconds
  -W, --linger=N             number of seconds to wait for response

 Options valid for --echo requests:

  -f, --flood                flood ping (root only)
      --ip-timestamp=FLAG    IP timestamp of type FLAG, which is one of
                             "tsonly" and "tsaddr"
  -l, --preload=NUMBER       send NUMBER packets as fast as possible before
                             falling into normal mode of behavior (root only)
  -p, --pattern=PATTERN      fill ICMP packet with given pattern (hex)
  -q, --quiet                quiet output
  -R, --route                record route
  -s, --size=NUMBER          send NUMBER data octets

  -?, --help                 give this help list
      --usage                give a short usage message
  -V, --version              print program version

Mandatory or optional arguments to long options are also mandatory or optional
for any corresponding short options.

Options marked with (root only) are available only to superuser.

Report bugs to <bug-inetutils@gnu.org>.
*/

void print_help(void)
{
	printf("Usage: ft_ping [OPTION...] HOST ...\n");
	printf("Send ICMP ECHO_REQUEST packets to network hosts.\n");
	printf("\n");
	printf(" Options controlling ICMP request types:\n");
	printf("      --address              send ICMP_ADDRESS packets (root only)\n");
	printf("      --echo                 send ICMP_ECHO packets (default)\n");
	printf("      --mask                 same as --address");
	printf("      --timestamp            send ICMP_TIMESTAMP packets");
	printf("  -t, --type=TYPE            send TYPE packets");
	printf("\n");
	printf(" Options valid for all request types:\n");
	printf("\n");
	printf("  -c, --count=NUMBER         stop after sending NUMBER packets\n");
	printf("  -d, --debug                set the SO_DEBUG option\n");
	printf("  -i, --interval=NUMBER      wait NUMBER seconds between sending each packet\n");
	printf("  -n, --numeric              do not resolve host addresses\n");
	printf("  -r, --ignore-routing       send directly to a host on an attached network\n");
	printf("      --ttl=N                specify N as time-to-live\n");
	printf("  -T, --tos=NUM              set type of service (TOS) to NUM\n");
	printf("  -v, --verbose              verbose output\n");
	printf("  -w, --timeout=N            stop after N seconds\n");
	printf("  -W, --linger=N             number of seconds to wait for response\n");
	printf("\n");
	printf(" Options valid for --echo requests:\n");
	printf("\n");
	printf("  -f, --flood                flood ping (root only)\n");
	printf("      --ip-timestamp=FLAG    IP timestamp of type FLAG, which is one of\n");
	printf("                             \"tsonly\" and \"tsaddr\"\n");
	printf("  -l, --preload=NUMBER       send NUMBER packets as fast as possible before\n");
	printf("                             falling into normal mode of behavior (root only)\n");
	printf("  -p, --pattern=PATTERN      fill ICMP packet with given pattern (hex)\n");
	printf("  -q, --quiet                quiet output\n");
	printf("  -R, --route                record route\n");
	printf("  -s, --size=NUMBER          send NUMBER data octets\n");
	printf("\n");
	printf("  -?, --help                 give this help list\n");
	printf("      --usage                give a short usage message\n");
	printf("  -V, --version              print program version\n");
	printf("\n");
	printf("Mandatory or optional arguments to long options are also mandatory or optional\n");
	printf("for any corresponding short options.\n");
	printf("\n");
	printf("Options marked with (root only) are available only to superuser.\n");
	printf("\n");
	printf("Report bugs to <bug-inetutils@gnu.org>.\n");	
}

void error_func(const char *msg)
{
	write(STDERR_FILENO, msg, sizeof(msg));
	write(STDERR_FILENO, "\n", 1);
	exit(EXIT_FAILURE);
}

void error_getaddrinfo(void)
{
	const char msg[] = "ft_ping: unknown protocol icmp.";

	write(STDERR_FILENO, msg, sizeof(msg));
	write(STDERR_FILENO, "\n", 1);
	exit(EXIT_FAILURE);
}