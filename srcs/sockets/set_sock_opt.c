#include "ft_ping.h"

void	set_recv_sock_opt(int fd_socket)
{
	struct icmp_filter	filter;
	struct timeval		timeout;

	filter.data = 1 << ICMP_ECHO;
	if (setsockopt(fd_socket, SOL_RAW, ICMP_FILTER, &filter, sizeof(filter)) == -1)
	{
		perror("ft_ping");
		close(fd_socket);
		exit(1);
	}
	timeout.tv_sec = 1;
	timeout.tv_usec = 0;
	if (setsockopt(fd_socket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout)) < 0)
	{
		perror("ft_ping");
		close(fd_socket);
		exit(1);
	}
}

void	set_send_sock_opt(int fd_socket)
{
	int broadcast;

	broadcast = 1;
	if (setsockopt(fd_socket, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast)) < 0)
	{
	    perror("ft_ping");
	    exit(1);
	}
}
