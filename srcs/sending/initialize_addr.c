#include "ft_ping.h"

struct sockaddr_in	initialize_addr(char *ipv4_addr)
{
	struct sockaddr_in	dest_addr;

	memset(&dest_addr, 0, sizeof(dest_addr));
	dest_addr.sin_family = AF_INET;
	if (!inet_pton(AF_INET, ipv4_addr, &dest_addr.sin_addr))
	{
		fprintf(stderr, "ft_ping: unknown host\n");
		exit(1);
	}
	return dest_addr;
}
