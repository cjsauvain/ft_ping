#include "ft_ping.h"

static void	extract_reply(t_reply_pckt *reply_pckt, char *buffer)
{
	struct icmphdr	icmphdr;

	memcpy(&reply_pckt->iphdr, buffer, IP_HDR_SIZE);
	memcpy(&icmphdr, buffer + IP_HDR_SIZE, ICMP_HDR_SIZE);
	if (icmphdr.type == 0)
	{
		reply_pckt->status_flags |= ECHO_REPLY;
		reply_pckt->echo_reply.icmphdr = icmphdr;
		memcpy(&reply_pckt->echo_reply.data, \
			buffer + IP_HDR_SIZE + ICMP_HDR_SIZE, ICMP_DATA_SIZE);
	}
	else
	{
		reply_pckt->status_flags &= ~ECHO_REPLY;
		memcpy(&reply_pckt->error_reply, \
			buffer + IP_HDR_SIZE, IP_HDR_SIZE + 2 * ICMP_HDR_SIZE);
	}
}

static int	recv_ip_pckt(t_ping *ping)
{
	char			buffer[BUFFER_SIZE];
	ssize_t			bytes_received;

	memset(buffer, 0, BUFFER_SIZE);
	bytes_received = recv(ping->recv_socket, buffer, BUFFER_SIZE, 0);
	if (bytes_received == -1)
	{
		ping->reply_pckt.status_flags |= NO_BYTES_RECEIVED;
		return -1;
	}
	ping->reply_pckt.status_flags &= ~NO_BYTES_RECEIVED;
	extract_reply(&ping->reply_pckt, buffer);
	return bytes_received;
}

void	receive_echo_reply(t_ping *ping)
{
	u_int8_t	*status_flags;
	int			sig;

	status_flags = &ping->reply_pckt.status_flags;
	sig = 0;
	while (!sig)
	{
		if (g_sig_triggered)
			sig = 1;
		if (recv_ip_pckt(ping) == -1)
			return ;
		process_reply(ping);
		if (*status_flags & VALID_ID)
			return ;
	}
}
