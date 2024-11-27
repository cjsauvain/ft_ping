#include "ft_ping.h"

int	ft_ping(t_command command)
{
	int					fd_socket;
	struct icmphdr		icmp;
	struct sockaddr_in	dest_addr;

	fd_socket = create_socket();
	dest_addr = initialize_addr(command.ip_addr);
	icmp = create_icmp_packet();
	send_echo_request(fd_socket, &dest_addr, &icmp);
	receive_echo_reply(fd_socket, &dest_addr);

	(void)command;

	return (0);
}
