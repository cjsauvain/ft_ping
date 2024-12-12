#include "ft_ping.h"

static void	ping_loop(int fd_socket, t_ping *ping, char *dest_addr_str)
{
	send_echo_request(fd_socket, ping);
	display_data_sent(dest_addr_str);
	receive_echo_reply(fd_socket, ping);
	while (!g_sigint_triggered)
	{
		usleep(ONE_SEC);
		send_echo_request(fd_socket, ping);
		receive_echo_reply(fd_socket, ping);
	}
	display_ping_stats(ping->stats.sent_pckt, ping->stats.received_pckt);
}

static void	run_ping(t_ping *ping, char **argv)
{
	int		fd_socket;

	fd_socket = create_socket();
	ping->icmp_pckt.icmphdr = create_icmp_hdr();
	ping->dest_addr = get_addr_struct(*argv);
	ping_loop(fd_socket, ping, *argv);
}

int	ft_ping(int argc, char **argv)
{
	t_ping	ping;
	int		first_addr_index;

	first_addr_index = 0;
	signal(SIGINT, handler);
	ping = parsing(argc, argv, &first_addr_index);
	argv += first_addr_index;
	run_ping(&ping, argv);
	return 0;
}
