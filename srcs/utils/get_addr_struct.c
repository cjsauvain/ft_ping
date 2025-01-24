#include "ft_ping.h"

int	get_addr_struct(struct sockaddr *dest_addr_struct, char *dest_addr)
{
	struct addrinfo	hints, *res;
	int				status;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_RAW;
	status = getaddrinfo(dest_addr, NULL, &hints, &res);
	if (status)
	{
		fprintf(stderr, "ft_ping: %s\n", gai_strerror(status));
		return -1;
	}
	*dest_addr_struct = *res->ai_addr;
	freeaddrinfo(res);
	return 0;
}
