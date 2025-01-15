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

static suseconds_t	initialize_icmp_data(char *data)
{
	struct timeval	tv_request;

	if (gettimeofday(&tv_request, NULL) == -1)
		return -1;;
	memcpy(data, &tv_request, sizeof(tv_request) / 2);
	randomly_fill_data(data);

	return get_time_microseconds(tv_request);
}

void	send_echo_request(t_ping *ping)
{
	ping->stats.tv_request = initialize_icmp_data(ping->icmp_pckt_request.data);
	if (ping->stats.tv_request == -1)
		clean_exit(ping->send_socket, ping->recv_socket, ping->stats.rtt_list, 1);
	ping->icmp_pckt_request.icmphdr.checksum = \
				process_checksum((unsigned short *)&ping->icmp_pckt_request);
	if (sendto(ping->send_socket, &ping->icmp_pckt_request, ICMP_PCKT_SIZE, 0, \
			ping->dest_addr, sizeof(*ping->dest_addr)) == - 1)
		clean_exit(ping->send_socket, ping->recv_socket, ping->stats.rtt_list, 1);
	ping->stats.sent_pckt++;
	ping->icmp_pckt_request.icmphdr.un.echo.sequence++;
	ping->icmp_pckt_request.icmphdr.checksum = 0;
}
