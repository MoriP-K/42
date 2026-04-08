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

ネットワークインターフェース eth0 を流れる ICMP パケットをリアルタイムで表示するコマンド。
ft_ping が実際にパケットを送受信しているかを目視確認するのに使った。

```text
tcpdump -i eth0 icmp -n
         │       │    │
         │       │    └─ -n: IPアドレスをホスト名に逆引きしない（数字のまま表示）
         │       └────── icmp: ICMPパケットだけフィルタ（TCP/UDP等は無視）
         └────────────── -i eth0: eth0 インターフェースを監視
```

- SOCK_RAW
  - 実行にはsudoが必要
    - OSの管理をバイパスしIPヘッダやTCP／UDPヘッダなどパケットの生のデータを直接作成・送受信できる
  - パケットの偽装（Spoofing）
    - 送信もとIPアドレスやポート番号を書き換えて他の機器になりすましてパケットを送信できできてしまう
  - 通信の盗聴
    - ネットワークインターフェースを通過する他ユーザのパケットも含め全パケットを受信できるから管理者権限が必要
- \_\_attribute_\_((packed))
  - コンパイラはCPUが読み書きしやすいように4バイト境界などでアラインメントしようとする
  - これは効率を無視してパディングをゼロにする
    - パケットやバイナリファイルでよく使う
