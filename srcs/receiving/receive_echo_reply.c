#include "ft_ping.h"

static bool	check_packet_id(struct icmphdr reply, struct icmphdr request)
{
	if (reply.un.echo.id != request.un.echo.id)
		return false;
	return true;
}

static int	recv_ip_pckt(int recv_socket, struct sockaddr *dest_addr, \
							t_reply_pckt *reply_pckt)
{
	char		buffer[BUFFER_SIZE];
	ssize_t		bytes_received;
	socklen_t	addr_len;

	memset(buffer, 0, BUFFER_SIZE);
	addr_len = sizeof(struct sockaddr_in);
	bytes_received = recvfrom(recv_socket, buffer, BUFFER_SIZE, 0, \
					dest_addr, &addr_len);
	if (bytes_received == -1)
		return -1;
	memcpy(&reply_pckt->iphdr, buffer, IP_HDR_SIZE);
	memcpy(&reply_pckt->icmp_pckt.icmphdr, buffer + IP_HDR_SIZE, ICMP_HDR_SIZE);
	memcpy(reply_pckt->icmp_pckt.data, buffer + IP_HDR_SIZE + ICMP_HDR_SIZE, ICMP_DATA_SIZE);

	return bytes_received;
}

ssize_t	receive_echo_reply(t_ping *ping)
{
	int		sigint;
	ssize_t	bytes_received;
	int		status;

	sigint = 0;
	bytes_received = -1;
	while (!sigint && bytes_received == -1)
	{
		if (g_sigint_triggered)
			sigint = 1;
		bytes_received = recv_ip_pckt(ping->recv_socket, \
							&ping->dest_addr, &ping->reply_pckt);
		if (bytes_received == -1)
			return -1;
		status = update_timestamps(&ping->stats);
		if (status < 0)
			clean_exit(ping->send_socket, ping->recv_socket, \
				ping->stats.rtt_list, status * -1);
		if (check_packet_id(ping->reply_pckt.icmp_pckt.icmphdr, \
				ping->icmp_pckt_request.icmphdr) == false)
		{
			bytes_received = -1;
			continue ;
		}
		if (check_checksum_reply(&ping->reply_pckt.icmp_pckt))
			return -1;
		ping->stats.received_pckt++;
	}
	return bytes_received;
}
