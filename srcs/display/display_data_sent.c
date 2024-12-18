#include "ft_ping.h"

void	display_data_sent(char *dest_addr, struct sockaddr_in *dest_addr_struct)
{
	char	dest_addr_buffer[MAX_IPV4_LEN];

	get_source_ip_addr(dest_addr_buffer, dest_addr_struct->sin_addr.s_addr);
	printf("PING %s (%s): %d data bytes\n", dest_addr, \
			dest_addr_buffer, ICMP_DATA_SIZE);
}
