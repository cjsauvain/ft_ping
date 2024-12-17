#include "ft_ping.h"

static struct iphdr	*recv_ip_pckt(int fd_socket, struct sockaddr *dest_addr, \
						t_ping_stats *stats)
{
	struct iphdr	*iphdr;
	socklen_t		addr_len;
	char			buffer[BUFFER_SIZE];
	ssize_t			bytes_received;

	memset(buffer, 0, sizeof(buffer));
	addr_len = sizeof(struct sockaddr_in);
	bytes_received = recvfrom(fd_socket, buffer, BUFFER_SIZE, 0, \
					dest_addr, &addr_len);
	if (bytes_received == -1)
		return NULL;
	update_timestamps(stats);
	iphdr = (struct iphdr *)buffer;

	return iphdr;
}

void	receive_echo_reply(int fd_socket, t_ping *ping)
{
	struct iphdr	*ip_reply;
	struct icmphdr	*icmp_reply;

	ip_reply = recv_ip_pckt(fd_socket, &ping->dest_addr, &ping->stats);
	ping->stats.received_pckt++;
	if (!ip_reply)
		return ;
	icmp_reply = (struct icmphdr *)((char *)ip_reply + 20);
	if (check_checksum_reply(icmp_reply))
		return ;
	display_reply(ip_reply, icmp_reply->un.echo.sequence, \
					ping->stats);
}
