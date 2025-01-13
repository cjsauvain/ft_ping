#include "ft_ping.h"

static void	send_left_dest_addr_packets(t_ping *ping, char **argv)
{
	while (*argv)
	{
		if (*argv[0] != '-')
		{
			ping->stats.sent_pckt = 0;
			ping->stats.received_pckt = 0;
			ping->dest_addr = get_addr_struct(*argv);
			send_echo_request(ping);
			display_data_sent(*argv, \
				(struct sockaddr_in *)&ping->dest_addr, ping->verbose_mode, \
				ping->icmp_pckt_request.icmphdr.un.echo.id);
			display_transmission_stats(ping->stats.sent_pckt, \
				ping->stats.received_pckt, *argv);
		}
		argv++;
	}
}

static void	ping_loop(t_ping *ping, char *dest_addr_str)
{
	ssize_t	bytes_received;

	send_echo_request(ping);
	bytes_received = receive_echo_reply(ping);
	display_data_sent(dest_addr_str, \
		(struct sockaddr_in *)&ping->dest_addr, ping->verbose_mode, \
		ping->icmp_pckt_request.icmphdr.un.echo.id);
	if (bytes_received != -1)
		display_reply(ping->reply_pckt, ping->stats);
	while (!g_sigint_triggered)
	{
		usleep(ONE_SEC);
		send_echo_request(ping);
		bytes_received = receive_echo_reply(ping);
		if (bytes_received != -1)
			display_reply(ping->reply_pckt, ping->stats);
	}
	printf("^C");
	display_ping_stats(ping->stats, dest_addr_str);
	free(ping->stats.rtt_list);
}

void	run_ping(t_ping *ping, char **argv)
{
	create_sockets(&ping->send_socket, &ping->recv_socket);
	ping->dest_addr = get_addr_struct(*argv);
	ping->icmp_pckt_request.icmphdr = create_icmp_hdr();
	ping_loop(ping, *argv);
	send_left_dest_addr_packets(ping, argv + 1);
	close_sockets(ping->send_socket, ping->recv_socket);
}
