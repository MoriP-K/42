# ft_traceroute
The  hints argument points to an addrinfo structure 
that specifies criteria for selecting the socket address structures 
returned in the list pointed to by res.
hints引数はresによって指されたリストに返された選択しているソケットアドレス構造体の基準を特定するaddrinfo構造体を指す

If hints is not NULL  it  points  to  an  addrinfo  structure 
whose ai_family, ai_socktype, and ai_protocol specify criteria 
that limit the set of socket addresses returned by getaddrinfo(), as follows:
もしHintsがNULLならば、 ai_family, ai_socktype, ai_protocolがgetaddrinfo()で返されたソケットアドレスのセットを制限する基準を特定するaddrinfo構造体を指す。