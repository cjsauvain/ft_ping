#include "ft_ping.h"

static void	display_data_sent(char *addr, size_t icmp_pckt_size)
{
	size_t			size;

	size = ICMP_PCKT_SIZE - icmp_pckt_size;
	printf("PING %s (%s): %ld data bytes\n", addr, addr, size);
}

static void	ping_loop(int fd_socket, struct sockaddr_in *dest_addr, \
				struct icmphdr *icmp_pckt, t_ping ping, int addr_index)
{
	struct timeval	tv_request;

	tv_request = send_echo_request(fd_socket, dest_addr, icmp_pckt, \
									&ping.sent_pckt);
	display_data_sent(ping.addr[addr_index], sizeof(icmp_pckt));
	receive_echo_reply(fd_socket, dest_addr, tv_request, &ping.received_pckt);
	while (!g_sigint_triggered)
	{
		usleep(ONE_SEC);
		tv_request = send_echo_request(fd_socket, dest_addr, \
										icmp_pckt, &ping.sent_pckt);
		receive_echo_reply(fd_socket, dest_addr, tv_request, \
							&ping.received_pckt);
	}
	display_ping_stats(ping.sent_pckt, ping.received_pckt);
	free(ping.addr);
	exit(0);
}

static void	run_ping(t_ping ping)
{
	int					fd_socket;
	struct icmphdr		icmp_pckt;
	struct sockaddr_in	dest_addr;
	int					i;

	fd_socket = create_socket();
	i = 0;
	while (ping.addr[i])
	{
		dest_addr = initialize_addr(ping.addr[i], ping.addr_buf);
		icmp_pckt = create_icmp_packet();
		ping_loop(fd_socket, &dest_addr, &icmp_pckt, ping, i);
		i++;
	}
}

int	ft_ping(int argc, char **argv)
{
	t_ping	ping;

	signal(SIGINT, handler);
	ping = parsing(argc, argv);
	run_ping(ping);
	return 0;
}
