#include "ft_ping.h"

static void	randomly_fill_data(char *data)
{
	int	i;

	srand(time(NULL));
	i = sizeof(struct timeval) / 2;
	while (i < ICMP_DATA_SIZE)
	{
		data[i] = rand() >> 24;
		i++;
	}
}

static struct timeval	initialize_icmp_data(char *data)
{
	struct timeval	tv_request;

	gettimeofday(&tv_request, NULL);
	memcpy(data, &tv_request, sizeof(tv_request) / 2);
	randomly_fill_data(data);

	return tv_request;
}

void	send_echo_request(int fd_socket, t_ping *ping)
{
	ping->stats.tv_request = initialize_icmp_data(ping->icmp_pckt.data);
	ping->icmp_pckt.icmphdr.checksum = \
				process_checksum((unsigned short *)&ping->icmp_pckt);
	if (sendto(fd_socket, &ping->icmp_pckt, ICMP_PCKT_SIZE, 0, \
			&ping->dest_addr, sizeof(ping->dest_addr)) == - 1)
	{
		perror("ft_ping: sending packet");
		exit(1);
	}
	ping->stats.sent_pckt++;
	ping->icmp_pckt.icmphdr.un.echo.sequence++;
	ping->icmp_pckt.icmphdr.checksum = 0;
}
