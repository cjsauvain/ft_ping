#include "ft_ping.h"

static char	*get_source_ip_addr(unsigned int saddr)
{
	struct in_addr 	ip_addr;
	char			*buffer;

	ip_addr.s_addr = saddr;
	buffer = inet_ntoa(ip_addr);

	return buffer;
}

static void	get_latency(char *latency_str, struct timeval tv_request, struct timeval tv_reply)
{
	float	latency_float;
	int		i;

	latency_float = (tv_reply.tv_sec - tv_request.tv_sec) * 1000 \
						+ (tv_reply.tv_usec - tv_request.tv_usec) / 1000.0;
	snprintf(latency_str, 10, "%.03f", latency_float);

	i = 0;
	while (latency_str[i] && latency_str[i] != '.')
		i++;
	latency_str[i] = ',';
}

void	display_reply(struct iphdr *ip_reply, struct icmphdr *icmp_reply, \
			struct timeval tv_request, struct timeval tv_reply)
{
	char	*source_ip_addr;
	int		icmp_pckt_size;
	char	latency[10];

	source_ip_addr = get_source_ip_addr(ip_reply->saddr);
	icmp_pckt_size = ntohs(ip_reply->tot_len) - (ip_reply->ihl * 4);
	get_latency(latency, tv_request, tv_reply);
	printf("%d bytes from %s: icmp_seq=%d ttl=%d time=%s ms\n",	\
			icmp_pckt_size, source_ip_addr, icmp_reply->un.echo.sequence, \
			ip_reply->ttl, latency);
}

