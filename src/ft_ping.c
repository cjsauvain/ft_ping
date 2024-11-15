#include "ft_ping.h"

static unsigned short	process_checksum(unsigned short *icmp_buffer, int icmphdr_len)
{
	unsigned int	sum;
	unsigned short	checksum;

	sum = 0;
	while (icmphdr_len > 1)
	{
		sum += *icmp_buffer++;
		icmphdr_len -= 2;
	}
	if (icmphdr_len > 0)
		sum += *(unsigned char *)icmp_buffer;
	while (sum >> 16)
		sum = (sum & 0xffff) + (sum >> 16);

	checksum = ~sum;
	return checksum;
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

static struct sockaddr_in	initialize_addr(void)
{
	struct sockaddr_in	addr;

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

	return addr;
}

static void	send_echo_request(int fd_socket, struct sockaddr_in *addr, struct icmphdr *icmp)
{
	char			buffer[56];
	unsigned short	checksum;

	memcpy(buffer, icmp, sizeof(struct icmphdr));
	checksum = process_checksum((unsigned short *)buffer, sizeof(struct icmphdr) + 48);
	*(buffer + 2) = checksum & 0xFF;
	*(buffer + 3) = checksum >> 8;
	sendto(fd_socket, buffer, 56, 0, (struct sockaddr *)addr, sizeof(*addr));
}

static void	receive_echo_reply(int fd_socket, struct sockaddr_in *addr)
{
	socklen_t	addr_len;
	char		buffer[56];

	addr_len = sizeof(addr);
	if (recvfrom(fd_socket, buffer, 56, 0, (struct sockaddr *)addr, &addr_len) == -1)
		printf("Could not receive packet\n");
}

static int	create_socket(void)
{
	int	fd_socket;

	fd_socket = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (fd_socket == -1)
	{
		fprintf(stderr, "Could not create socket...\n");
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
