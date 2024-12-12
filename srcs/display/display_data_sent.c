#include "ft_ping.h"

void	display_data_sent(char *dest_addr)
{
	printf("PING %s (%s): %d data bytes\n", dest_addr, dest_addr, ICMP_DATA_SIZE);
}
