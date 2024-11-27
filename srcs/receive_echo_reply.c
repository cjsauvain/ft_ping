#include "ft_ping.h"

void	receive_echo_reply(int fd_socket, struct sockaddr_in *dest_addr)
{
	socklen_t		addr_len;
	char			buffer[1500];
	struct icmphdr	*icmp_reply;

	addr_len = sizeof(dest_addr);
	if (recvfrom(fd_socket, buffer, 1500, 0, (struct sockaddr *)dest_addr, &addr_len) == -1)
	{
		fprintf(stderr, "Could not receive packet...\n");
		exit(1);
	}
	icmp_reply = (struct icmphdr *)(buffer + 20);
	if (icmp_reply->un.echo.id == 0)
		return ;
}
