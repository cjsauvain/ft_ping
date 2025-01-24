#include "ft_ping.h"

static void display_echo_reply_output(t_reply_pckt reply_pckt, t_ping_stats stats)
{
	char			source_addr[MAX_IPV4_LEN];
	int				icmp_pckt_size;

	memset(source_addr, 0, MAX_IPV4_LEN);
	get_source_addr(source_addr, reply_pckt.iphdr.saddr);
	icmp_pckt_size = ntohs(reply_pckt.iphdr.tot_len) - (reply_pckt.iphdr.ihl * 4);
	printf("%d bytes from %s: icmp_seq=%d ttl=%d time=%ld.%03ld ms\n",	\
		icmp_pckt_size, source_addr, \
		reply_pckt.icmp_pckt.icmphdr.un.echo.sequence, \
		reply_pckt.iphdr.ttl, stats.tv_rtt / 1000, stats.tv_rtt % 1000);
}

void	display_reply(t_ping *ping)
{
	u_int8_t	status_flags;

	status_flags = ping->reply_pckt.status_flags;
	if (status_flags & ECHO_REPLY && status_flags & VALID_CHECKSUM)
			display_echo_reply_output(ping->reply_pckt, ping->stats);
	else if (status_flags & VALID_CHECKSUM)
	{
		if (display_icmp_message(ping->reply_pckt, ping->verbose_mode))
			clean_exit(ping->send_socket, ping->recv_socket, \
				ping->stats.rtt_list, 1);
	}
}
