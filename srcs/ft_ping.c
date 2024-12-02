#include "ft_ping.h"

static void	ping_loop(int fd_socket, struct sockaddr_in *dest_addr, \
				struct icmphdr *icmp_pckt, char *addr)
{
	struct timeval	tv_request;
	size_t			size;

	tv_request = send_echo_request(fd_socket, dest_addr, \
					icmp_pckt);
	receive_echo_reply(fd_socket, dest_addr, tv_request);
	size = ICMP_PCKT_SIZE - sizeof(icmp_pckt);
	printf("PING %s (%s): %ld data bytes\n", addr, addr, size);
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
	int					i;

	fd_socket = create_socket();
	i = 0;
	while (command.addr[i])
	{
		dest_addr = initialize_addr(command.addr[i]);
		icmp_pckt = create_icmp_packet();
		ping_loop(fd_socket, &dest_addr, &icmp_pckt, command.addr[i]);
		i++;
	}
}

int	ft_ping(int argc, char **argv)
{
	t_command	command;

	//signal(SIGINT, handler);
	command = parsing(argc, argv);
	run_ping(command);
	return 0;
}
