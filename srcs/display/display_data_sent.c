#include "ft_ping.h"

void	display_data_sent(struct sockaddr_in dest_addr, size_t icmp_pckt_size)
{
	size_t			size;

	size = ICMP_PCKT_SIZE - icmp_pckt_size;
	printf("PING %s (%s): %ld data bytes\n", addr, addr, size);
}
