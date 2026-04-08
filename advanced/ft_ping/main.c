#include <sys/socket.h>
#include <sys/errno.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

struct s_icmp_test
{
	u_int8_t type;
	u_int8_t code;
	u_int16_t checksum;
	u_int16_t id;
	u_int16_t sequence;
	uint32_t data;
} __attribute__((packed));

u_int16_t checksum(void *data, size_t len)
{
	u_int32_t sum;
	u_int16_t *ptr;

	printf("len: %zu\n", len);
	sum = 0;
	ptr = (u_int16_t *)data;
	while (len > 1)
	{
		sum += *ptr++;
		len -= 2;
	}
	if (len == 1)
		sum += *(u_int8_t *)ptr << 8;
	while (sum >> 16)
		sum = (sum >> 16) + (sum & 0xFFFF);
	return (u_int16_t)~sum;
}

int main(void)
{
	// add: option from args

	// add: getaddrinfo()

	int sock_fd = socket(AF_INET, SOCK_RAW, 1);
	if (sock_fd == -1)
	{
		perror("socket");
	}
	// u_int16_t data[] = {0x01, 0x00, 0x01};
	// printf("checksum: %x\n", checksum(data, sizeof(data)));

	struct s_icmp_test packet;

	memset(&packet, 0, sizeof(struct s_icmp_test));
	packet.type = 8; // Echo Request
	packet.code = 0;
	packet.id = htons(0x1234);
	packet.sequence = htons(0x0001);
	packet.data = 0xdeadbeef;
	packet.checksum = checksum(&packet, sizeof(packet));
	printf("checksum: %x\n", packet.checksum);

	unsigned char *raw = (unsigned char *)&packet;
	printf("Memory dump (first 4 bytes): %02x %02x %02x %02x\n", raw[0], raw[1], raw[2], raw[3]);

	struct sockaddr_in sock_in;

	memset(&sock_in, 0, sizeof(struct sockaddr_in));
	sock_in.sin_family = AF_INET;
	sock_in.sin_addr.s_addr = inet_addr("127.0.0.1");
	sock_in.sin_port = 0;

	while (1)
	{
		// add signal handle
		ssize_t n = sendto(sock_fd, &packet, sizeof(packet), 0, (struct sockaddr *)&sock_in, sizeof(sock_in));
		if (n < 0)
		{
			perror("sendto");
			break;
		}
		else
		printf("success!\n");
		// add: Round Trip Time
		char buf[1024];
		struct sockaddr_in from;
		socklen_t from_len;
		from_len = sizeof(from);
		ssize_t rec = recvfrom(sock_fd, buf, sizeof(buf), 0, (struct sockaddr *)&from, &from_len);
		if (rec > 0)
		{
			struct s_icmp_test *reply = (struct s_icmp_test *)(buf + 20);
			printf("received type: %d, code: %d\n", reply->type, reply->code);
		}
		sleep(1);
	}
	// add: print result
}