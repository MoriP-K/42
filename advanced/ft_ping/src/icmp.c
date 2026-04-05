#include "../include/ft_ping.h"
#include <sys/time.h>

uint16_t checksum(void *data, int len)
{
	uint16_t *buf;
	uint32_t sum;
	
	buf = data;
	sum = 0;
	while (len > 1)
	{
		sum += *buf++;
		len -= 2;
	}
	if (len == 1)
		sum += *(uint8_t *)buf;
	sum = (sum >> 16) + (sum & 0xFFFF);
	sum += (sum >> 16);
	return (~sum);
	
}

void send_ping(t_ping *ping)
{
	char packet[PING_PACKET_SIZE];
	t_icmp_header *hdr;
	struct timeval *tv;
	ssize_t ret;

	// initialize
	memset(packet, 0, sizeof(packet));
	// pointer of header
	hdr = (t_icmp_header *)packet;
	hdr->type = ICMP_ECHO_REQUEST;
	hdr->code = 0;
	hdr->id = htons(ping->icmp_id);
	hdr->sequence = htons(ping->icmp_seq);
	hdr->checksum = 0;
	// set timestamp
	tv = (struct timeval *)(packet + sizeof(t_icmp_header));
	gettimeofday(tv, NULL);
	// calculate checksum
	hdr->checksum = checksum(packet, sizeof(packet));
	// send
	ret = sendto(ping->sockfd, packet, sizeof(packet), 0, (struct sockaddr *)&ping->dest_addr, sizeof(ping->dest_addr));
	if (ret < 0)
		perror("sendto");
	else
		ping->packets_sent++;
	// increment seq number
	ping->icmp_seq++;
}