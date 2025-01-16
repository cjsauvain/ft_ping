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

static int display_bytes_from(u_int32_t saddr, int icmp_pckt_size, u_int8_t type, u_int8_t code)
{
	char				source_hostname[9];
	char				source_ip[MAX_IPV4_LEN];
	char				icmp_message[ICMP_MESSAGE_MAXLEN];
	struct sockaddr_in	dest_addr;
		
	if (get_addr_struct((struct sockaddr *)&dest_addr, "_gateway") == -1)
		return -1;
	if (saddr == dest_addr.sin_addr.s_addr)
		strcpy(source_hostname, "_gateway");
	else
		get_source_addr(source_hostname, saddr);
	get_source_addr(source_ip, saddr);
	get_icmp_type_message(icmp_message, type, code);
	printf("%d bytes from %s (%s): %s\n", icmp_pckt_size, source_hostname, \
											source_ip, icmp_message);
	return 0;
}

int	display_icmp_message(t_reply_pckt reply_pckt, bool verbose_mode)
{
	int			icmp_pckt_size;
	u_int8_t	type;
	u_int8_t	code;

	icmp_pckt_size = ntohs(reply_pckt.iphdr.tot_len) - (reply_pckt.iphdr.ihl * 4);
	type = reply_pckt.icmp_pckt.icmphdr.type;
	code = reply_pckt.icmp_pckt.icmphdr.code;

	if (display_bytes_from(reply_pckt.iphdr.saddr, icmp_pckt_size, type, code))
		return -1;
	if (verbose_mode == true)
		display_ip_hdr(reply_pckt.icmp_pckt);
	return 0;
}

