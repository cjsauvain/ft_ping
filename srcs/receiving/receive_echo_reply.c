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

void	receive_echo_reply(int fd_socket, t_ping *ping, int addr_index)
{
	struct iphdr	*ip_reply;
	struct icmphdr	*icmp_reply;
	struct sockaddr	*dest_addr;
	struct timeval	tv_reply;

	dest_addr = (struct sockaddr *)&ping->dest_addr_list[addr_index];
	ip_reply = recv_ip_pckt(fd_socket, dest_addr, &tv_reply);
	icmp_reply = (struct icmphdr *)((char *)ip_reply + 20);
	if (check_checksum_reply(icmp_reply))
		return ;
	display_reply(ip_reply, icmp_reply, tv_reply, tv_reply);
	ping->stats.received_pckt++;
}
