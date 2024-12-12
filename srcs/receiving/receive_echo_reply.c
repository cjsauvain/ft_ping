#include "ft_ping.h"

static struct iphdr	*recv_ip_pckt(int fd_socket, struct sockaddr *dest_addr, \
						struct timeval *tv_reply)
{
	struct iphdr	*ip_reply;
	socklen_t		addr_len;
	char			buffer[IP_HDR_SIZE + ICMP_PCKT_SIZE];

	addr_len = sizeof(dest_addr);
	if (recvfrom(fd_socket, buffer, IP_HDR_SIZE + ICMP_PCKT_SIZE, \
				0, dest_addr, &addr_len) == -1)
	{
		fprintf(stderr, "Could not receive packet...\n");//do not exit program
		exit(1);
	}
	gettimeofday(tv_reply, NULL);
	ip_reply = (struct iphdr *)buffer;
	return ip_reply;

}

static void	display_icmp_reply(struct icmphdr *icmp_reply)
{
	unsigned char	*paquet;

	paquet = (unsigned char *)icmp_reply;
	for (size_t i = 0; i < ICMP_PCKT_SIZE; i++)
	{
       	printf("%02x ", paquet[i]);
       	if ((i + 1) % 16 == 0)
           	printf("\n");
		else
			printf(" ");
    }
}

void	receive_echo_reply(int fd_socket, t_ping *ping)
{
	struct iphdr	*ip_reply;
	struct icmphdr	*icmp_reply;

	ip_reply = recv_ip_pckt(fd_socket, &ping->dest_addr, &ping->stats.tv_reply);
	icmp_reply = (struct icmphdr *)((char *)ip_reply + 20);
	display_icmp_reply(icmp_reply);
	if (check_checksum_reply(icmp_reply))
		return ;
	display_reply(ip_reply, icmp_reply, ping->stats.tv_request, \
					ping->stats.tv_reply);
	ping->stats.received_pckt++;
}
