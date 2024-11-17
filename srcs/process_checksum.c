#include "ft_ping.h"

unsigned short	process_checksum(unsigned short *icmp_buffer, int icmphdr_len)
{
	unsigned int	sum;
	unsigned short	checksum;

	sum = 0;
	while (icmphdr_len > 1)
	{
		sum += *icmp_buffer++;
		icmphdr_len -= 2;
	}
	if (icmphdr_len > 0)
		sum += *(unsigned char *)icmp_buffer;
	while (sum >> 16)
		sum = (sum & 0xffff) + (sum >> 16);

	checksum = ~sum;
	return checksum;
}
