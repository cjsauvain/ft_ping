#include "ft_ping.h"

struct sockaddr	get_addr_struct(char *dest_addr)
{
	struct addrinfo	hints, *res;
	struct sockaddr	dest_addr_struct;
	int				status;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_RAW;
	status = getaddrinfo(dest_addr, NULL, &hints, &res);
	if (status)
	{
		fprintf(stderr, "ft_ping: unknown host\n");
		exit(1);
	}
	dest_addr_struct = *res->ai_addr;
	freeaddrinfo(res);
	return dest_addr_struct;
}
