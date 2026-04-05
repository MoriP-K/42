- sockaddr_inは16byteの構造体
- sockaddrも16byteの構造体
```c
struct sockaddr							
{										
	sa_family_t sa_family;	// 2byte	
	char sa_data[14]; 		// 14bytes	
										
										
};

struct sockaddr_in
{
	sa_family_t sin_family;		← same position		// LINUXは2byte	
	in_port_t    sin_port;     	← sa_data[0..1]		// 2byte
	struct in_addr sin_addr;  	← sa_data[2..5]		// 4byte
	char sin_zero[8];      		← sa_data[6..13]	// 8byte
};										
```

`net_ntop`(network to presentation): バイトオーダーを4区切りのIPアドレスの文字列に変換