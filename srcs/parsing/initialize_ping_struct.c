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

	memset(&reply_pckt, 0, sizeof(reply_pckt));
	reply_pckt.status_flags = 0;

	return reply_pckt;
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

static struct sockaddr	initialize_dest_addr_struct(void)
{
	struct sockaddr dest_addr;

	memset(&dest_addr, 0, sizeof(dest_addr));
	return dest_addr;
}

t_ping	initialize_ping_struct(void)
{
	t_ping	ping;

	ping.echo_request = initialize_icmp_pckt();
	ping.reply_pckt = initialize_reply_pckt();
	ping.dest_addr = initialize_dest_addr_struct();
	ping.stats = initialize_ping_stats();
	ping.verbose_mode = false;
	ping.exit_status = 0;

	return ping;
}
