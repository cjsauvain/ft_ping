#include "ft_ping.h"

static void	prepare_buffer(struct icmphdr *icmp, char *buffer)
{
	unsigned short	checksum;

	memcpy(buffer, icmp, sizeof(struct icmphdr));
	checksum = process_checksum((unsigned short *)buffer, sizeof(struct icmphdr) + 48);
	*(buffer + 2) = checksum & 0xFF;
	*(buffer + 3) = checksum >> 8;
}

void	send_echo_request(int fd_socket, struct sockaddr_in *dest_addr, struct icmphdr *icmp)
{
	char			buffer[56];

	prepare_buffer(icmp, buffer);
	sendto(fd_socket, buffer, 56, 0, (struct sockaddr *)dest_addr, sizeof(*dest_addr));
}
