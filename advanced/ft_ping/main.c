#include <netinet/in.h>
#include <stdint.h>
#include <string.h>
#include <sys/_types/_u_int32_t.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

/*
	struct addrinfo {
		int ai_flags;           // input flags 
		int ai_family;          // protocol family for socket 
		int ai_socktype;        // socket type 
		int ai_protocol;        // protocol for socket 
		socklen_t ai_addrlen;   // length of socket-address 
		struct sockaddr *ai_addr; // socket-address for socket 
		char *ai_canonname;     // canonical name for service location 
		struct addrinfo *ai_next; // pointer to next in list 
	}
*/

int main() {
	struct addrinfo hints, *ai;
	memset(&hints, 0, sizeof(hints));
	ai = (struct addrinfo *)malloc(sizeof(*ai));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	// ai->ai_flags = AI_ADDRCONFIG;
	int8_t info = getaddrinfo("google.com", NULL, &hints, &ai);

	// printf("ai_flags=%d\nai_family=%d\nai_socktype=%d\nai_protocol=%d\nai_addrlen=%d\nai_addr.sa_family=%u\nai_addr.sa_data=%s\nai_canonname=%s\n", ai->ai_flags, ai->ai_family, ai->ai_socktype, ai->ai_protocol, ai->ai_addrlen, ai->ai_addr->sa_family, ai->ai_addr->sa_data, ai->ai_canonname);

	struct in_addr sa = ((struct sockaddr_in *)ai->ai_addr)->sin_addr;
	printf("sin_addr=%s\n", inet_ntoa(sa));
	void *ptr = &((struct sockaddr_in * )ai->ai_addr)->sin_addr;
	char addrbuf[32];
	const char *address = inet_ntop(ai->ai_family, ptr, addrbuf, sizeof(addrbuf));
	printf("address=%s\n", address);
	// u_int32_t a = 0x4;
	// u_int8_t *b = (u_int8_t *)&a;

	// printf("a=%d\n", a);
	// printf("b[0]=%d, b[1]=%d, b[2]=%d, b[3]=%d\n", b[0], b[1], b[2], b[3]);
}