#include "ft_ping.h"

static bool	check_packet_id(struct icmphdr reply, struct icmphdr request)
{
	if (reply.un.echo.id != request.un.echo.id)
		return false;
	return true;
}

static int	recv_ip_pckt(t_ping *ping)
{
	char			buffer[BUFFER_SIZE];
	ssize_t			bytes_received;
	int				status;

	memset(buffer, 0, BUFFER_SIZE);
	bytes_received = recv(ping->recv_socket, buffer, BUFFER_SIZE, 0);
	if (bytes_received == -1)
		return -1;
	memcpy(&ping->reply_pckt.iphdr, buffer, IP_HDR_SIZE);
	memcpy(&ping->reply_pckt.icmp_pckt.icmphdr, buffer + IP_HDR_SIZE, ICMP_HDR_SIZE);
	memcpy(ping->reply_pckt.icmp_pckt.data, buffer + IP_HDR_SIZE + ICMP_HDR_SIZE, ICMP_DATA_SIZE);

	status = update_timestamps(&ping->stats);
	if (status < 0)
		clean_exit(ping->send_socket, ping->recv_socket, \
			ping->stats.rtt_list, status * -1);
	return bytes_received;
}

ssize_t	receive_echo_reply(t_ping *ping)
{
	int		sig;
	ssize_t	bytes_received;

	sig = 0;
	bytes_received = -1;
	while (!sig && bytes_received == -1)
	{
		if (g_sig_triggered)
			sig = 1;
		bytes_received = recv_ip_pckt(ping);
		if (bytes_received == -1)
			return -1;
		if (ping->reply_pckt.icmp_pckt.icmphdr.type != 0)
			break ;
		if (check_packet_id(ping->reply_pckt.icmp_pckt.icmphdr, \
				ping->icmp_pckt_request.icmphdr) == false)
			bytes_received = -1;
		else if (check_checksum_reply(&ping->reply_pckt.icmp_pckt))
			return -1;
		ping->stats.received_pckt++;
	}
	if (ping->reply_pckt.icmp_pckt.icmphdr.type == 3)
		ping->unreachable = true;
	return bytes_received;
}
