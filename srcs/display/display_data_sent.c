#include "ft_ping.h"

void	display_data_sent(struct sockaddr_in dest_addr, size_t icmp_pckt_size)
{
	size_t	size;
	char	dest_addr_str[MAX_IPV4_LEN];

	size = ICMP_PCKT_SIZE - icmp_pckt_size;
	inet_ntop(AF_INET, &dest_addr.sin_addr.s_addr, dest_addr_str, MAX_IPV4_LEN);
	printf("PING %s (%s): %ld data bytes\n", dest_addr_str, dest_addr_str, size);
}
