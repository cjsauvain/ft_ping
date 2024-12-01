#include "ft_ping.h"

static struct timeval	prepare_buffer(struct icmphdr *icmp, char *buffer)
{
	unsigned short	checksum;
	struct timeval	tv;

	memcpy(buffer, icmp, sizeof(struct icmphdr));
	gettimeofday(&tv, NULL);
	memcpy(buffer + sizeof(struct icmphdr), &tv, sizeof(tv));
	checksum = process_checksum((unsigned short *)buffer, ICMP_PCKT_SIZE);
	*(buffer + 2) = checksum & 0xFF;
	*(buffer + 3) = checksum >> 8;

	return tv;
}

struct timeval	send_echo_request(int fd_socket, struct sockaddr_in *dest_addr, \
			struct icmphdr *icmp)
{
	char			buffer[ICMP_PCKT_SIZE];
	struct timeval	tv;

	tv = prepare_buffer(icmp, buffer);
	if (sendto(fd_socket, buffer, ICMP_PCKT_SIZE, 0, (struct sockaddr *)dest_addr, sizeof(*dest_addr)) == - 1)
	{
		fprintf(stderr, "Could not send packet...\n");
		exit(1);
	}
	return tv;
}
