#include "ft_ping.h"

int	check_checksum_reply(struct icmphdr *icmp_pckt)
{
	unsigned short	checksum_reply;
	unsigned short	checksum_tmp;

	checksum_tmp = icmp_pckt->checksum;
	icmp_pckt->checksum = 0;
	checksum_reply = process_checksum((unsigned short *)icmp_pckt);
	if (checksum_reply != checksum_tmp)
		return 1;
	icmp_pckt->checksum = checksum_tmp;
	return 0;
}
