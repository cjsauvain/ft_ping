#include "ft_ping.h"

struct icmphdr	create_icmp_packet(void)
{
	struct icmphdr	icmp;

	icmp.type = 8;
	icmp.code = 0;
	icmp.checksum = 0;
	icmp.un.echo.id = getpid();
	icmp.un.echo.sequence = 0;
	
	return icmp;
}
