#include "ft_ping.h"

static void	get_rtt_str(char *rtt_str, float ts_rtt)
{
	int	i;

	snprintf(rtt_str, 10, "%.03f", ts_rtt);
	i = 0;
	while (rtt_str[i] && rtt_str[i] != '.')
		i++;
	rtt_str[i] = ',';
}

void	display_reply(struct iphdr *ip_reply, int icmp_seq, t_ping_stats stats)
{
	char	source_ip_addr[MAX_IPV4_LEN];
	int		icmp_pckt_size;
	char	rtt_str[10];

	memset(source_ip_addr, 0, MAX_IPV4_LEN);
	get_source_ip_addr(source_ip_addr, ip_reply->saddr);
	icmp_pckt_size = ntohs(ip_reply->tot_len) - (ip_reply->ihl * 4);
	get_rtt_str(rtt_str, stats.ts_rtt);
	printf("%d bytes from %s: icmp_seq=%d ttl=%d time=%s ms\n",	\
			icmp_pckt_size, source_ip_addr, icmp_seq, ip_reply->ttl, rtt_str);
}

