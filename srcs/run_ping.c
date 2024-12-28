#include "ft_ping.h"

static void	send_left_dest_addr_packets(t_ping *ping, char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (argv[i][0] != '-')
		{
			ping->stats.sent_pckt = 0;
			ping->stats.received_pckt = 0;
			ping->dest_addr = get_addr_struct(*argv);
			send_echo_request(ping);
			display_data_sent(*argv, \
				(struct sockaddr_in *)&ping->dest_addr);
			display_transmission_stats(ping->stats.sent_pckt, \
				ping->stats.received_pckt);
		}
		i++;
	}
}

static void	ping_loop(t_ping *ping, char *dest_addr_str)
{
	ssize_t	bytes_received;

	send_echo_request(ping);
	bytes_received = receive_echo_reply(ping);
	display_data_sent(dest_addr_str, \
		(struct sockaddr_in *)&ping->dest_addr);
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
	display_ping_stats(ping->stats);
	free(ping->stats.rtt_list);
}

void	run_ping(t_ping *ping, char **argv)
{
	ping->dest_addr = get_addr_struct(*argv);
	ping->icmp_pckt_request.icmphdr = create_icmp_hdr();
	create_sockets(&ping->send_socket, &ping->recv_socket);
	ping_loop(ping, *argv);
	send_left_dest_addr_packets(ping, argv + 1);
	close_sockets(ping->send_socket, ping->recv_socket);
}
