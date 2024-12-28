#include "ft_ping.h"

static void	ping_loop(t_ping *ping, char *dest_addr_str)
{
	ssize_t	bytes_received;

	send_echo_request(ping);
	bytes_received = receive_echo_reply(ping);
	display_data_sent(dest_addr_str, (struct sockaddr_in *)&ping->dest_addr);
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
	close_sockets(ping->send_socket, ping->recv_socket);
}

static void	run_ping(t_ping *ping, char **argv)
{
	ping->dest_addr = get_addr_struct(*argv);
	ping->icmp_pckt_request.icmphdr = create_icmp_hdr();
	create_sockets(&ping->send_socket, &ping->recv_socket);
	ping_loop(ping, *argv);
}

int	ft_ping(int argc, char **argv)
{
	t_ping	ping;
	int		first_addr_index;

	first_addr_index = 0;
	init_signal_handler();
	ping = parsing(argc, argv, &first_addr_index);
	argv += first_addr_index;
	run_ping(&ping, argv);
	return 0;
}
