#ifndef FT_PING_H
# define FT_PING_H

# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/socket.h>
# include <linux/icmp.h>
# include <arpa/inet.h>
# include <netinet/ip.h>
#include <sys/time.h>

# define	ICMP_PCKT_SIZE	64

typedef struct s_command {
	int		status;
	char	*ip_addr;
	char	option[2];
}	t_command;

t_command			parsing(int argc, char **argv);
int					ft_ping(int argc, char **argv);
unsigned short		process_checksum(unsigned short *icmp_buffer, \
						int icmphdr_len);
struct timeval		send_echo_request(int fd_socket, \
						struct sockaddr_in *dest_addr, \
						struct icmphdr *icmp, char *ip_addr);
void				receive_echo_reply(int fd_socket, \
						struct sockaddr_in *dest_addr, \
						struct timeval tv_request);
int					create_socket(void);
struct sockaddr_in	initialize_addr(char *ip_addr);
struct icmphdr		create_icmp_packet(void);
void				display_reply(struct iphdr *ip_pckt, \
						struct icmphdr *icmp_pckt, \
						struct timeval tv_request, struct timeval tv_reply);
int					check_checksum_reply(struct icmphdr *icmp_pckt);

#endif
