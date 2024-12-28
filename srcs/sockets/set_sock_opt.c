#include "ft_ping.h"

void	set_sock_opt(int fd_socket)
{
	struct icmp_filter	filter;
	struct timeval		timeout;

	filter.data = ~(1 << ICMP_ECHOREPLY);
	if (setsockopt(fd_socket, SOL_RAW, ICMP_FILTER, &filter, sizeof(filter)) == -1)
	{
		perror("ft_ping");
		close(fd_socket);
		exit(1);
	}
	timeout.tv_sec = 0;
	timeout.tv_usec = 1;
	if (setsockopt(fd_socket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout)) < 0)
	{
		perror("ft_ping");
		close(fd_socket);
		exit(1);
	}
}
