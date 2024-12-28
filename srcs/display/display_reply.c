#include "ft_ping.h"

static void	get_rtt_str(char rtt_str[], suseconds_t tv_rtt)
{
	snprintf(rtt_str, 50, "%ld,%.03ld", tv_rtt / 1000, tv_rtt % 1000);
}

void	display_reply(t_reply_pckt reply_pckt, t_ping_stats stats)
{
	char	source_ip_addr[MAX_IPV4_LEN];
	int		icmp_pckt_size;
	char	rtt_str[50];

	memset(source_ip_addr, 0, MAX_IPV4_LEN);
	get_source_ip_addr(source_ip_addr, reply_pckt.iphdr.saddr);
	icmp_pckt_size = ntohs(reply_pckt.iphdr.tot_len) \
						- (reply_pckt.iphdr.ihl * 4);
	get_rtt_str(rtt_str, stats.tv_rtt);
	printf("%d bytes from %s: icmp_seq=%d ttl=%d time=%s ms\n",	\
		icmp_pckt_size, source_ip_addr, \
		reply_pckt.icmp_pckt.icmphdr.un.echo.sequence, \
		reply_pckt.iphdr.ttl, rtt_str);
}
