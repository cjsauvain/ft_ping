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

static void	initialize_icmp_data(char *data, double *ts_request)
{
	struct timeval	tv_request;

	gettimeofday(&tv_request, NULL);
	*ts_request = get_time_ms(tv_request);
	memcpy(data, &tv_request, sizeof(tv_request) / 2);
	randomly_fill_data(data);
}

void	send_echo_request(int fd_socket, t_ping *ping)
{
	initialize_icmp_data(ping->icmp_pckt.data, &ping->stats.ts_request);
	ping->icmp_pckt.icmphdr.checksum = \
				process_checksum((unsigned short *)&ping->icmp_pckt);
	if (sendto(fd_socket, &ping->icmp_pckt, ICMP_PCKT_SIZE, 0, \
			&ping->dest_addr, sizeof(ping->dest_addr)) == - 1)
	{
		fprintf(stderr, "ft_ping: could not send packet...\n");
		exit(1);
	}
	ping->stats.sent_pckt++;
	ping->icmp_pckt.icmphdr.checksum = 0;
}
