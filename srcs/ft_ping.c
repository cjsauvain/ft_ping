#include "ft_ping.h"

static void	ping_loop(int fd_socket, struct sockaddr_in *dest_addr, \
				struct icmphdr *icmp_pckt, char *ip_addr)
{
	struct timeval		tv_request;

	tv_request = send_echo_request(fd_socket, &dest_addr, \
					&icmp_pckt, command.ip_addr);
	receive_echo_reply(fd_socket, &dest_addr, tv_request);
	//print first and only ping banner
	while (1)
	{
		tv_request = send_echo_request(fd_socket, &dest_addr, \
						&icmp_pckt, command.ip_addr);
		receive_echo_reply(fd_socket, &dest_addr, tv_request);
	}
}

static void	run_ping(t_command command)
{
	int					fd_socket;
	struct icmphdr		icmp_pckt;
	struct sockaddr_in	dest_addr;

	fd_socket = create_socket();
	dest_addr = initialize_addr(command.ip_addr);
	icmp_pckt = create_icmp_packet();
	ping_loop(fd_socket, &dest_addr, &icmp_pckt, command.ip_addr)
}

int	ft_ping(int argc, char **argv)
{
	t_command	command;

	command = parsing(argc, argv);	
	run_ping(command);

	return 0;
}
