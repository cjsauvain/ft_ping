#include "ft_ping.h"

static void	extract_reply(t_reply_pckt *reply_pckt, char *buffer)
{
	memcpy(&reply_pckt->iphdr, buffer, IP_HDR_SIZE);
	memcpy(&reply_pckt->icmp_pckt.icmphdr, buffer + IP_HDR_SIZE, ICMP_HDR_SIZE);
	if (reply_pckt->icmp_pckt.icmphdr.type == 0)
		memcpy(&reply_pckt->icmp_pckt.data, \
				buffer + IP_HDR_SIZE + ICMP_HDR_SIZE, ICMP_DATA_SIZE);
	else
	{
		memcpy(&reply_pckt->icmp_error.original_iphdr, \
				buffer + IP_HDR_SIZE + ICMP_HDR_SIZE, IP_HDR_SIZE);
		memcpy(&reply_pckt->icmp_error.original_icmphdr, \
				buffer + 2 * IP_HDR_SIZE + ICMP_HDR_SIZE, ICMP_HDR_SIZE);
	}
}

static int	recv_ip_pckt(t_ping *ping)
{
	char			buffer[BUFFER_SIZE];
	ssize_t			bytes_received;

	memset(buffer, 0, BUFFER_SIZE);
	bytes_received = recv(ping->recv_socket, buffer, BUFFER_SIZE, 0);
	if (bytes_received == -1)
		return -1;
	extract_reply(&ping->reply_pckt, buffer);
	return bytes_received;
}

t_reply_status	receive_echo_reply(t_ping *ping)
{
	int				sig;
	ssize_t			bytes_received;
	t_reply_status	reply_status;

	sig = 0;
	bytes_received = -1;
	while (!sig && bytes_received == -1)
	{
		if (g_sig_triggered)
			sig = 1;
		bytes_received = recv_ip_pckt(ping);
		if (bytes_received == -1)
			return NO_BYTES_RECEIVED;
		reply_status = process_reply(ping);
		if (!(reply_status == ID_VALID))
		{
			bytes_received = -1;
			continue ;
		}
		else if (reply_status == ID_VALID)
		else if (reply_status == ID_VALID | ECHO_REPLY)
	}
	return PCKT_RECEIVED;
}
