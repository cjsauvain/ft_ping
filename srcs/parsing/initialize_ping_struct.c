#include "ft_ping.h"

static t_icmp_pckt	initialize_icmp_pckt(void)
{
	t_icmp_pckt	icmp_pckt;

	memset(&icmp_pckt, 0, ICMP_PCKT_SIZE);
	return icmp_pckt;
}

static t_reply_pckt	initialize_reply_pckt(void)
{
	t_reply_pckt	reply_pckt;

	memset(&reply_pckt.iphdr, 0, IP_HDR_SIZE);
	memset(&reply_pckt.icmp_pckt.icmphdr, 0, ICMP_HDR_SIZE);
	memset(&reply_pckt.icmp_pckt.data, 0, ICMP_DATA_SIZE);

	return reply_pckt;
}

static struct sockaddr	initialize_dest_addr(void)
{
	struct sockaddr	dest_addr;

	memset(&dest_addr, 0, sizeof(dest_addr));
	return dest_addr;
}

static t_ping_stats	initialize_ping_stats(void)
{
	t_ping_stats	stats;

	stats.sent_pckt = 0;
	stats.received_pckt = 0;
	stats.tv_request = 0;
	stats.tv_reply = 0; 
	stats.tv_min = 0;
	stats.tv_max = 0;
	stats.tv_avg = 0;
	stats.tv_stddev = 0;
	stats.tv_rtt = 0;
	stats.rtt_list = NULL;

	return stats;
}

static bool	initialize_verbose_mode(void)
{
	return false;
}

t_ping	initialize_ping_struct(void)
{
	t_ping	ping;

	ping.icmp_pckt_request = initialize_icmp_pckt();
	ping.reply_pckt = initialize_reply_pckt();
	ping.dest_addr = initialize_dest_addr();
	ping.stats = initialize_ping_stats();
	ping.verbose_mode = initialize_verbose_mode();

	return ping;
}
