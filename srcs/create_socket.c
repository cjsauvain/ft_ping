#include "ft_ping.h"

static void	set_sock_opt(int fd_socket)
{
	struct timeval		tv_exit;
	struct icmp_filter	filter;

	tv_exit.tv_sec = 3;
	tv_exit.tv_usec = 0;
	if (setsockopt(fd_socket, SOL_SOCKET, SO_RCVTIMEO, &tv_exit, sizeof(tv_exit)) == -1)
	{
		fprintf(stderr, "Could not set socket options...\n");
		exit(1);
	}

	filter.data = ~(1 << ICMP_ECHOREPLY);
	if (setsockopt(fd_socket, SOL_RAW, ICMP_FILTER, &filter, sizeof(filter)) == -1)
	{
		fprintf(stderr, "Could not set socket options...\n");
		exit(1);
	}
}

int	create_socket(void)
{
	int				fd_socket;

	fd_socket = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (fd_socket == -1)
	{
		fprintf(stderr, "Could not create socket...\n");
		exit(1);
	}
	set_sock_opt(fd_socket);
	return fd_socket;
}
