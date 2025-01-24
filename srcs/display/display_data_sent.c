#include "ft_ping.h"

void	display_data_sent(char *dest_addr, char *dest_addr_ip, \
			bool verbose_mode, \
			u_int16_t echo_request_id)
{
	printf("PING %s (%s): %d data bytes", dest_addr, \
			dest_addr_ip, ICMP_DATA_SIZE);
	if (verbose_mode == true)
		printf(", id 0x%hx = %hu\n", echo_request_id, echo_request_id);
	else
		printf("\n");
}
