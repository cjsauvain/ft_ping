#include "ft_ping.h"

static struct iphdr	*recv_ip_pckt(int fd_socket, struct sockaddr_in *dest_addr, \
						struct timeval *tv_reply)
{
	struct iphdr	*ip_reply;
	socklen_t		addr_len;
	char			buffer[1500];

	addr_len = sizeof(dest_addr);
	if (recvfrom(fd_socket, buffer, 1500, 0, (struct sockaddr *)dest_addr, &addr_len) == -1)
	{
		fprintf(stderr, "Could not receive packet...\n");//do not exit program
		exit(1);
	}
	gettimeofday(tv_reply, NULL);
	ip_reply = (struct iphdr *)buffer;
	return ip_reply;

}

void	receive_echo_reply(int fd_socket, struct sockaddr_in *dest_addr, \
			struct timeval tv_request)
{
	struct iphdr	*ip_reply;
	struct icmphdr	*icmp_reply;
	struct timeval	tv_reply;

	ip_reply = recv_ip_pckt(fd_socket, dest_addr, &tv_reply);
	icmp_reply = (struct icmphdr *)((char *)ip_reply + 20);
	if (check_checksum_reply(icmp_reply))
		return ;
	display_reply(ip_reply, icmp_reply, tv_request, tv_reply);
}
