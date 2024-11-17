#include "ft_ping.h"

void	receive_echo_reply(int fd_socket, struct sockaddr_in *addr)
{
	socklen_t		addr_len;
	char			buffer[1500];
	//struct icmphdr	*icmp_reply;

	addr_len = sizeof(addr);
	if (recvfrom(fd_socket, buffer, 1500, 0, (struct sockaddr *)addr, &addr_len) == -1)
	{
		fprintf(stderr, "Could not receive packet...\n");
		exit(1);
	}
	/*
	icmp_reply = (struct icmphdr *)(buffer);
	printf("type = %02x\n", icmp_reply->type);
	printf("code = %02x\n", icmp_reply->code);
	printf("checksum = %04x\n", ntohs(icmp_reply->checksum));*/
	for (int i = 1; i <= 76; i++)
	{
		printf("%02x ", (unsigned char)buffer[i - 1]);
		if (!(i % 16))
			printf("\n");
	}
	printf("\n");
}
