#include "ft_ping.h"

struct icmphdr	create_icmp_hdr(void)
{
	struct icmphdr	icmp;

	icmp.type = ICMP_ECHO;
	icmp.code = 0;
	icmp.checksum = 0;
	icmp.un.echo.id = getpid();
	icmp.un.echo.sequence = 0;
	
	return icmp;
}
