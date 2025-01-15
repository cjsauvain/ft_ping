#include "ft_ping.h"

static void	get_icmp_type_message(char *icmp_message, u_int8_t type, u_int8_t code)
{
	if (type == 3)
		get_destination_unreachable_message(icmp_message, code);
	if (type == 4)
		get_source_quench_message(icmp_message);
	if (type == 5)
		get_redirect_message(icmp_message, code);
	if (type == 11)
		get_time_exceeded_message(icmp_message, code);
	if (type == 12)
		get_parameter_problem_message(icmp_message, code);
}

static int	display_icmp_message(u_int32_t saddr, int icmp_pckt_size, \
									u_int8_t type, u_int8_t code)
{
	char				source_hostname[9];
	char				source_ip[MAX_IPV4_LEN];
	char				icmp_message[ICMP_MESSAGE_MAXLEN];
	struct sockaddr_in	*dest_addr;
		
	dest_addr = (struct sockaddr_in *)get_addr_struct("_gateway");
	if (!dest_addr)
		return -1;
	if (saddr == dest_addr->sin_addr.s_addr)
		strcpy(source_hostname, "_gateway");
	else
		get_source_addr(source_hostname, saddr);
	get_source_addr(source_ip, saddr);
	get_icmp_type_message(icmp_message, type, code);
	printf("%d bytes from %s (%s): %s\n", icmp_pckt_size, source_hostname, \
											source_ip, icmp_message);

	return 0;
}

void	display_reply(t_reply_pckt reply_pckt, t_ping_stats stats, \
						int send_socket, int recv_socket)
{
	char			source_addr[MAX_IPV4_LEN];
	int				icmp_pckt_size;
	struct icmphdr	icmphdr;

	icmphdr = reply_pckt.icmp_pckt.icmphdr;

	icmp_pckt_size = ntohs(reply_pckt.iphdr.tot_len) - (reply_pckt.iphdr.ihl * 4);
	if (icmphdr.type == 0)
	{
		memset(source_addr, 0, MAX_IPV4_LEN);
		get_source_addr(source_addr, reply_pckt.iphdr.saddr);
		printf("%d bytes from %s: icmp_seq=%d ttl=%d time=%ld.%03ld ms\n",	\
			icmp_pckt_size, source_addr, \
			reply_pckt.icmp_pckt.icmphdr.un.echo.sequence, \
			reply_pckt.iphdr.ttl, stats.tv_rtt / 1000, stats.tv_rtt % 1000);
		return ;
	}
	if (display_icmp_message(reply_pckt.iphdr.saddr, icmp_pckt_size, icmphdr.type, icmphdr.code))
		clean_exit(send_socket, recv_socket, stats.rtt_list, 1);
}
