#include "ft_ping.h"

static void	display_iphdr_fields(struct iphdr *iphdr)
{
	u_int32_t	saddr;
	u_int32_t	daddr;

	saddr = ntohl(iphdr->saddr);
	daddr = ntohl(iphdr->daddr);
	
	printf("\nVr HL TOS  Len   ID Flg  off TTL Pro  cks      Src	Dst	Data\n ");
	printf("%x  ", iphdr->version);
	printf("%x  ", iphdr->ihl);
	printf("%.02x ", iphdr->tos);
	printf("%.04x ", ntohs(iphdr->tot_len));
	printf("%x   ", ntohs(iphdr->id));
	printf("%x ", ntohs(iphdr->frag_off) >> 13);
	printf("%.04x  ", ntohs(iphdr->frag_off) & 0x1F00);
	printf("%.02x  ", iphdr->ttl);
	printf("%.02x ", iphdr->protocol);
	printf("%x ", ntohs(iphdr->check));
	printf("%d.%d.%d.%d  ", (saddr >> 24) & 0xFF, (saddr >> 16) & 0xFF, \
		(saddr >> 8) & 0xFF, saddr & 0xFF);
	printf("%d.%d.%d.%d\n", (daddr >> 24) & 0xFF, (daddr >> 16) & 0xFF, \
		(daddr >> 8) & 0xFF, daddr & 0xFF);
}

static void display_iphdr_dump(unsigned short *iphdr)
{
	int	i;

	i = 0;
	while (i < IP_HDR_SIZE / 2)
	{
		printf(" %.4x", ntohs(*(iphdr + i)));
		i++;
	}
	display_iphdr_fields((struct iphdr *)iphdr);
}

static void	display_icmp_hdr(struct icmphdr *icmp_pckt_request)
{
	printf("ICMP: type %d, code %d, size %d, id 0x%x, seq 0x%.04x\n", \
		icmp_pckt_request->type, icmp_pckt_request->code, \
		ICMP_PCKT_SIZE, icmp_pckt_request->un.echo.id, \
		icmp_pckt_request->un.echo.sequence);
}

void	display_ip_hdr(t_icmp_pckt icmp_pckt_reply)
{
	unsigned short	*iphdr_request;
	struct icmphdr	*icmp_pckt_request;

	printf("IP Hdr Dump:\n");
	iphdr_request = (unsigned short *)&icmp_pckt_reply + ICMP_HDR_SIZE / 2;
	icmp_pckt_request = (struct icmphdr *)(iphdr_request + IP_HDR_SIZE / 2);
	display_iphdr_dump(iphdr_request);
	display_icmp_hdr(icmp_pckt_request);
}
