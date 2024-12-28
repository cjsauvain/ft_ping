#include "ft_ping.h"

int	check_checksum_reply(t_icmp_pckt *icmp_pckt)
{
	unsigned short	checksum_reply;
	unsigned short	checksum_tmp;

	checksum_tmp = icmp_pckt->icmphdr.checksum;
	icmp_pckt->icmphdr.checksum = 0;
	checksum_reply = process_checksum((unsigned short *)icmp_pckt);
	if (checksum_reply != checksum_tmp)
		return 1;
	icmp_pckt->icmphdr.checksum = checksum_tmp;
	return 0;
}
