#include "ft_ping.h"

void	display_reply(t_reply_pckt reply_pckt, t_ping_stats stats)
{
	char	source_ip_addr[MAX_IPV4_LEN];
	int		icmp_pckt_size;

	memset(source_ip_addr, 0, MAX_IPV4_LEN);
	get_source_ip_addr(source_ip_addr, reply_pckt.iphdr.saddr);
	icmp_pckt_size = ntohs(reply_pckt.iphdr.tot_len) \
						- (reply_pckt.iphdr.ihl * 4);
	printf("%d bytes from %s: icmp_seq=%d ttl=%d time=%ld.%03ld ms\n",	\
		icmp_pckt_size, source_ip_addr, \
		reply_pckt.icmp_pckt.icmphdr.un.echo.sequence, \
		reply_pckt.iphdr.ttl, stats.tv_rtt / 1000, stats.tv_rtt % 1000);
}
