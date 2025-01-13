#include "ft_ping.h"

void	create_sockets(int *send_socket, int *recv_socket)
{
	*recv_socket = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (*recv_socket == -1)
	{
		fprintf(stderr, "ft_ping: Lacking privilege for icmp socket.\n");
		exit(1);
	}
	set_sock_opt(*recv_socket);

	*send_socket = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (*send_socket == -1)
	{
		fprintf(stderr, "ft_ping: Lacking privilege for icmp socket.\n");
		close(*recv_socket);
		exit(1);
	}
}
