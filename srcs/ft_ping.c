#include "ft_ping.h"

static struct sockaddr_in	initialize_addr(void)
{
	struct sockaddr_in	addr;

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

	return addr;
}

static struct icmphdr	create_icmp_packet(void)
{
	struct icmphdr	icmp;

	icmp.type = 8;
	icmp.code = 0;
	icmp.checksum = 0;
	icmp.un.echo.id = getpid();
	icmp.un.echo.sequence = 0;
	
	return (icmp);
}

static int	create_socket(void)
{
	int				fd_socket;
	struct timeval	tv_exit;

	fd_socket = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (fd_socket == -1)
	{
		fprintf(stderr, "Could not create socket...\n");
		exit(1);
	}
	tv_exit.tv_sec = 1;
	tv_exit.tv_usec = 0;
	if (setsockopt(fd_socket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv_exit, sizeof tv_exit) == -1)
	{
		fprintf(stderr, "Could not set socket options...\n");
		exit(1);
	}
	return fd_socket;
}

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
