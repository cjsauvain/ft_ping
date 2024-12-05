#include "ft_ping.h"

static void	get_ipv4_format(char *addr, char *addr_buf)
{
	struct addrinfo		hints, *res;
	struct sockaddr_in	*ipv4_struct;
	void				*ipv4;
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
	ipv4_struct = (struct sockaddr_in *)res->ai_addr;
	ipv4 = &(ipv4_struct->sin_addr);
	inet_ntop(res->ai_family, ipv4, addr_buf, MAX_IPV4_LEN);
}

static t_addr_format	check_addr_format(char *addr)
{
	int	i;

	i = 0;
	while (addr[i])
	{
		if (!isdigit(addr[i]) && addr[i] != '.')
			return HOSTNAME_FORMAT;
		i++;
	}
	return IPV4_FORMAT;
}

struct sockaddr_in	initialize_addr(char *addr, char *addr_buf)
{
	struct sockaddr_in	dest_addr;

	memset(&dest_addr, 0, sizeof(dest_addr));
	dest_addr.sin_family = AF_INET;
	if (check_addr_format(addr) == HOSTNAME_FORMAT)
		get_ipv4_format(addr, addr_buf);
	else
		addr_buf = strcpy(addr_buf, addr);
	if (!inet_pton(AF_INET, addr_buf, &dest_addr.sin_addr))
	{
		fprintf(stderr, "ft_ping: unknown host\n");
		exit(1);
	}
	return dest_addr;
}
