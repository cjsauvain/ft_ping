#include "ft_ping.h"

static void	send_left_dest_addr_packets(t_ping *ping, char **argv)
{
	char				dest_addr_ip[MAX_IPV4_LEN];
	struct sockaddr_in	*dest_addr_struct;

	dest_addr_struct = (struct sockaddr_in *)&ping->dest_addr;
	while (*argv)
	{
		if (*argv[0] != '-')
		{
			get_source_addr(dest_addr_ip, dest_addr_struct->sin_addr.s_addr);
			ping->stats.sent_pckt = 0;
			ping->stats.received_pckt = 0;
			display_data_sent(*argv, dest_addr_ip, ping->verbose_mode, \
				ping->echo_request.icmphdr.un.echo.id);
			send_echo_request(ping);
			display_transmission_stats(ping->stats.sent_pckt, \
				ping->stats.received_pckt, *argv);
		}
		argv++;
	}
}

static void	first_sending(t_ping *ping, u_int8_t *status_flags, char *dest_addr_str)
{
	char				dest_addr_ip[MAX_IPV4_LEN];
	struct sockaddr_in	*dest_addr_struct;

	dest_addr_struct = (struct sockaddr_in *)&ping->dest_addr;
	get_source_addr(dest_addr_ip, dest_addr_struct->sin_addr.s_addr);
	display_data_sent(dest_addr_str, dest_addr_ip, ping->verbose_mode, \
		ping->echo_request.icmphdr.un.echo.id);
	send_echo_request(ping);
	receive_echo_reply(ping);
	if (*status_flags & VALID_ID && !(*status_flags & NO_BYTES_RECEIVED))
		display_reply(ping);
	usleep(WAIT);
}

static void	ping_loop(t_ping *ping, char *dest_addr_str)
{
	u_int8_t	*status_flags;

	status_flags = &ping->reply_pckt.status_flags;
	first_sending(ping, status_flags, dest_addr_str);
	while (g_sig_triggered == NO_SIGNAL)
	{
		send_echo_request(ping);
		receive_echo_reply(ping);
		if (*status_flags & VALID_ID && !(*status_flags & NO_BYTES_RECEIVED))
			display_reply(ping);
		usleep(WAIT);
	}
	display_sig();
	if (g_sig_triggered == SIG_INT)
		display_ping_stats(ping->stats, dest_addr_str);
	if (!ping->stats.received_pckt)
		ping->exit_status = 1;
}

void	run_ping(t_ping *ping, char **argv)
{
	create_sockets(&ping->send_socket, &ping->recv_socket);
	if (get_addr_struct(&ping->dest_addr, *argv) == -1)
		clean_exit(ping->send_socket, ping->recv_socket, ping->stats.rtt_list, 1);
	ping->echo_request.icmphdr = create_icmp_hdr();
	ping_loop(ping, *argv);
	send_left_dest_addr_packets(ping, argv + 1);
	close_sockets(ping->send_socket, ping->recv_socket);
}
