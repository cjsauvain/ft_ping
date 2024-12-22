#include "ft_ping.h"

static void	set_sock_opt(int fd_socket)
{
	struct icmp_filter	filter;

	filter.data = ~(1 << ICMP_ECHOREPLY);
	if (setsockopt(fd_socket, SOL_RAW, ICMP_FILTER, &filter, sizeof(filter)) == -1)
	{
		perror("ft_ping: ");
		exit(1);
	}
}

int	create_socket(void)
{
	int				fd_socket;

	fd_socket = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (fd_socket == -1)
	{
		fprintf(stderr, "ft_ping: Lacking privilege for icmp socket...\n");
		exit(1);
	}
	set_sock_opt(fd_socket);
	return fd_socket;
}
