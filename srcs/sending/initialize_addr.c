#include "ft_ping.h"

static void	get_ipv4_format(char *addr)
{
	struct addrinfo	hints, *res;
	int				status;

	hints.ai_family = AF_INET;
	ints.ai_socktype = SOCK_RAW;
	status = getaddrinfo(addr, NULL, &hints, &res);
	if (status)
	{
		gai_strerror(status);
		exit(status);
	}

}

struct sockaddr_in	initialize_addr(char *addr)
{
	struct sockaddr_in	dest_addr;

	memset(&dest_addr, 0, sizeof(dest_addr));
	dest_addr.sin_family = AF_INET;
	if (check_addr_format(addr) == HOSTNAME_FORMAT)
		get_ipv4_format(addr);
	if (!inet_pton(AF_INET, addr, &dest_addr.sin_addr))
	{
		fprintf(stderr, "ft_ping: unknown host\n");
		exit(1);
	}
	return dest_addr;
}
