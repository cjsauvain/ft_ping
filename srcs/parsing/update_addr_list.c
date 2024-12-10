#include "ft_ping.h"

static struct sockaddr_in	get_addr_struct(char *addr)
{
	struct addrinfo		hints, *res;
	struct sockaddr_in	*addr_struct;
	int					status;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_RAW;
	status = getaddrinfo(addr, NULL, &hints, &res);
	if (status)
	{
		fprintf(stderr, "%s\n", gai_strerror(status));
		exit(status);
	}
	addr_struct = (struct sockaddr_in *)res->ai_addr;
	return *addr_struct;
}

struct sockaddr_in	*update_addr_list(char **argv, int addr_count)
{
	struct sockaddr_in	*p_dest_addr_list;
	struct sockaddr_in	dest_addr_list[addr_count];
	int					i;
	int					j;

	i = 0;
	j = 0;
	while (i < addr_count)
	{
		if (argv[i][0] != '-')
			dest_addr_list[j++] = get_addr_struct(argv[i]);
		i++;
	}
	p_dest_addr_list = dest_addr_list;
	return p_dest_addr_list;
}
