#include "ft_ping.h"

int	ft_ping(t_command command)
{
	int					fd_socket;
	struct icmphdr		icmp;
	struct sockaddr_in	addr;

	fd_socket = create_socket();
	addr = initialize_addr();
	icmp = create_icmp_packet();
	send_echo_request(fd_socket, &addr, &icmp);
	receive_echo_reply(fd_socket, &addr);

	(void)command;

	return (0);
}
