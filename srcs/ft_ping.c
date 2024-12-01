#include "ft_ping.h"

static void	ping_loop(int fd_socket, struct sockaddr_in *dest_addr, \
				struct icmphdr *icmp_pckt, char *ipv4_addr)
{
	struct timeval	tv_request;
	size_t			size;

	tv_request = send_echo_request(fd_socket, dest_addr, \
					icmp_pckt);
	receive_echo_reply(fd_socket, dest_addr, tv_request);
	size = ICMP_PCKT_SIZE - sizeof(icmp_pckt);
	printf("PING %s (%s): %ld data bytes\n", ipv4_addr, ipv4_addr, size);
	while (1)
	{
		tv_request = send_echo_request(fd_socket, dest_addr, \
						icmp_pckt);
		receive_echo_reply(fd_socket, dest_addr, tv_request);
	}
}

static void	run_ping(t_command command)
{
	int					fd_socket;
	struct icmphdr		icmp_pckt;
	struct sockaddr_in	dest_addr;

	fd_socket = create_socket();
	dest_addr = initialize_addr(command.ipv4_addr);
	icmp_pckt = create_icmp_packet();
	ping_loop(fd_socket, &dest_addr, &icmp_pckt, command.ipv4_addr);
}

int	ft_ping(int argc, char **argv)
{
	t_command	command;

	//signal(SIGINT, handler);
	command = parsing(argc, argv);	
	while (1)
		run_ping(command);
	return 0;
}
