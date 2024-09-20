#include "ft_ping.h"

struct icmphdr	*create_icmp_packet(void)
{
	struct icmphdr	*icmp = malloc(sizeof(struct icmphdr *));;

	if (!icmp)
		return (NULL);
	icmp->type = 8;
	icmp->code = 0;
	icmp->checksum = 0;
	icmp->un.echo.id = htons(getpid());
	icmp->un.echo.sequence = 0;
	
	return (icmp);
}

unsigned short	process_checksum(unsigned short *icmphdr, int icmphdr_len)
{
	uint16_t	sum = 0;

	while (icmphdr_len > 1)
	{
		sum += ntohs(*(icmphdr++));
		icmphdr_len -= 2;
	}
	if (icmphdr_len)
		sum += ntohs(*icmphdr);
	while (sum >> 16)
		sum = ntohs((sum & 0xffff) + (sum >> 16));
	return (htons(~sum));
}

int	ft_ping(t_command command)
{
	(void)command;
	int					fd_socket;
	struct icmphdr		*icmp;
	char				buffer[48];
	char				data[] ="\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f !\"#$%&'";
	char				*p = buffer;
	struct sockaddr_in	addr;
	size_t				icmp_len;
	int					i = 0;

	fd_socket = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (fd_socket == -1)
	{
		fprintf(stderr, "Could not create socket...\n");
		return (-1);
	}
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	icmp = create_icmp_packet();
	if (!icmp)
		return (-1);
	p += sizeof(icmp);
	*(p++) = data[i++];
	while (data[i])
		*(p++) = data[i++];
	icmp_len = sizeof(icmp);
	memcpy(buffer, icmp, icmp_len);
	icmp->checksum = process_checksum((unsigned short *)icmp, sizeof(icmp));
	memcpy(buffer, icmp, icmp_len);
	sendto(fd_socket, buffer, 48, 0, (const struct sockaddr *)&addr, sizeof(addr));
	//recvfrom(fd_socket, buffer, 2000, 0, (const struct sockaddr *)addr, sizeof(addr));
	return (0);
}
