#include "ft_ping.h"

static struct timeval	initialize_icmp_data(char *data)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	memcpy(data, &tv, sizeof(tv));
	//randomly fill left data octets

	return tv;
}

struct void	send_echo_request(int fd_socket, t_ping *ping, int addr_index)
{
	struct sockaddr	*dest_addr;

	ping->tv_sent = initialize_icmp_data(ping->icmp_pckt.data);
	ping->icmp_pckt.icmphdr.checksum = \
				process_checksum((unsigned short *)&ping->icmp_pckt);
	dest_addr = (struct sockaddr *)ping->dest_addr_list[addr_index];
	if (sendto(fd_socket, &ping->icmp_pckt, ICMP_PCKT_SIZE, 0, \
			dest_addr, sizeof(*dest_addr)) == - 1)
	{
		fprintf(stderr, "Could not send packet...\n");
		exit(1);
	}
	ping->stats.sent_pckt++;
}
