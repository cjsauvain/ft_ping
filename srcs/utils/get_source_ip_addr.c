#include "ft_ping.h"

void	get_source_ip_addr(char *buffer, unsigned int saddr)
{
	struct in_addr 	ip_addr;

	ip_addr.s_addr = saddr;
	strcpy(buffer, inet_ntoa(ip_addr));
}
