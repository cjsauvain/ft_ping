#include "ft_ping.h"

void	display_data_sent(char *dest_addr, \
			struct sockaddr_in *dest_addr_struct, \
			bool verbose_mode, \
			u_int16_t echo_request_id)
{
	char	dest_addr_buffer[MAX_IPV4_LEN];

	get_source_ip_addr(dest_addr_buffer, dest_addr_struct->sin_addr.s_addr);
	printf("PING %s (%s): %d data bytes", dest_addr, \
			dest_addr_buffer, ICMP_DATA_SIZE);
	if (verbose_mode == true)
		printf(", id 0x%hx = %hu\n", echo_request_id, echo_request_id);
	else
		write(1, "\n", 1);
}
