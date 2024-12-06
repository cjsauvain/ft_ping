#include "ft_ping.h"

static void	ping_loop(int fd_socket, t_ping *ping, int addr_index)
{
	send_echo_request(fd_socket, ping, addr_index);
	display_data_sent(ping->dest_addr_list[addr_index], sizeof(ping->icmp_pckt));
	receive_echo_reply(fd_socket, ping, addr_index);
	while (!g_sigint_triggered)
	{
		usleep(ONE_SEC);
		send_echo_request(fd_socket, ping, addr_index);
		receive_echo_reply(fd_socket, ping, addr_index);
	}
	display_ping_stats(ping->stats.sent_pckt, ping->stats.received_pckt);
	exit(0);
}

static void	run_ping(t_ping *ping)
{
	int	fd_socket;
	int	i;

	fd_socket = create_socket();
	i = 0;
	while (ping->dest_addr_list[i])
	{
		ping->icmp_pckt.icmphdr = create_icmp_hdr();
		ping_loop(fd_socket, ping, i);
		i++;
	}
}

int	ft_ping(int argc, char **argv)
{
	t_ping	ping;

	signal(SIGINT, handler);
	ping = parsing(argc, argv);
	run_ping(&ping);
	return 0;
}
