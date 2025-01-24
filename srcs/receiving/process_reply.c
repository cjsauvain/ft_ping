#include "ft_ping.h"

static u_int8_t	check_packet_id(struct icmphdr hdr1, struct icmphdr hdr2)
{
	if (hdr1.un.echo.id != hdr2.un.echo.id)
		return 0;
	return VALID_ID;
}

static void	process_icmp_error(struct icmphdr icmphdr_request, \
			struct icmphdr request_icmphdr_returned, u_int8_t *status_flags)
{
	u_int8_t	id_check;
	u_int8_t	checksum_check;

	id_check = check_packet_id(icmphdr_request, request_icmphdr_returned);
	checksum_check = 0;
	if (icmphdr_request.checksum == request_icmphdr_returned.checksum)
		checksum_check = VALID_CHECKSUM;

	*status_flags &= ~ECHO_REPLY;
	*status_flags = (id_check == VALID_ID) \
						? (*status_flags | VALID_ID) \
						: (*status_flags & ~VALID_ID);
	*status_flags = (checksum_check == VALID_CHECKSUM) \
						? (*status_flags | VALID_CHECKSUM) \
						: (*status_flags & ~VALID_CHECKSUM);
}

static void	process_echo_reply(t_ping *ping)
{
	u_int8_t	*status_flags;
	u_int8_t	id_check;
	u_int8_t	checksum_check;
	int			status;

	status_flags = &ping->reply_pckt.status_flags;
	id_check = check_packet_id(ping->reply_pckt.echo_reply.icmphdr, \
			ping->echo_request.icmphdr);
	checksum_check = check_checksum_reply(&ping->reply_pckt.echo_reply);

	*status_flags |= ECHO_REPLY;
	*status_flags = (id_check == VALID_ID) \
						? (*status_flags | VALID_ID) \
						: (*status_flags & ~VALID_ID);
	*status_flags = (checksum_check == VALID_CHECKSUM) \
						? (*status_flags | VALID_CHECKSUM) \
						: (*status_flags & ~VALID_CHECKSUM);
	if (*status_flags & VALID_ID && *status_flags & VALID_CHECKSUM)
	{
		status = update_timestamps(&ping->stats);
		if (status < 0)
			clean_exit(ping->send_socket, ping->recv_socket, \
				ping->stats.rtt_list, status * -1);
		ping->stats.received_pckt++;
	}
}

void	process_reply(t_ping *ping)
{
	if (ping->reply_pckt.status_flags & ECHO_REPLY)
		process_echo_reply(ping);
	else
		process_icmp_error(ping->echo_request.icmphdr, \
			ping->reply_pckt.error_reply.original_icmphdr, &ping->reply_pckt.status_flags);
}
