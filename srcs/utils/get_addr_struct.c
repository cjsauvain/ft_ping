#include "ft_ping.h"

static void	free_res(struct addrinfo *res)
{
	struct addrinfo	*tmp;

	while (res)
	{
		tmp = res->ai_next;
		free(res);
		res = tmp;
	}
}

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
		fprintf(stderr, "ft_ping: %s\n", gai_strerror(status));
		exit(1);
	}
	dest_addr_struct = *res->ai_addr;
	free_res(res);
	return dest_addr_struct;
}

