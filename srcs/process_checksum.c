#include "ft_ping.h"

unsigned short	process_checksum(unsigned short *icmp_pckt)
{
	unsigned int	sum;
	unsigned short	checksum;
	int				icmphdr_len;

	sum = 0;
	icmphdr_len = ICMP_PCKT_SIZE;
	while (icmphdr_len > 1)
	{
		sum += *icmp_pckt++;
		icmphdr_len -= 2;
	}
	if (icmphdr_len > 0)
		sum += *(unsigned char *)icmp_pckt;
	while (sum >> 16)
		sum = (sum & 0xffff) + (sum >> 16);

	checksum = ~sum;
	return checksum;
}
