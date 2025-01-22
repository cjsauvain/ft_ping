#include "ft_ping.h"

static bool	check_packet_id(struct icmphdr reply, struct icmphdr request)
{
	if (reply.un.echo.id != request.un.echo.id)
		return false;
	return true;
}

t_reply_status	process_reply(t_ping *ping)
{
	if (ping->reply_pckt.icmp_pckt.icmphdr.type != 0)
		break ;
	if (check_packet_id(ping->reply_pckt.icmp_pckt.icmphdr, \
			ping->icmp_pckt_request.icmphdr) == false)
	if (check_checksum_reply(&ping->reply_pckt.icmp_pckt))
	status = update_timestamps(&ping->stats);
	if (status < 0)
		clean_exit(ping->send_socket, ping->recv_socket, \
			ping->stats.rtt_list, status * -1);
	ping->stats.received_pckt++;
	return PCKT_RECEIVED;
}
