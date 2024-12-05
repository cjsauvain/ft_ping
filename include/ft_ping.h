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
# include <sys/time.h>
# include <ctype.h>
# include <signal.h>
# include <netdb.h>
# include <stdbool.h>

# define	ICMP_PCKT_SIZE	64
# define	ONE_SEC			1000000
# define	MAX_IPV4_LEN	16

extern bool	g_sigint_triggered;

typedef enum e_addr_format
{
	IPV4_FORMAT,
	HOSTNAME_FORMAT,
}	t_addr_format;

typedef struct s_ping
{
	char	**addr;
	char	addr_buf[MAX_IPV4_LEN];
	bool	verbose_mode;
	int		sent_pckt;
	int		received_pckt;
}	t_ping;

t_ping				parsing(int argc, char **argv);
int					ft_ping(int argc, char **argv);
unsigned short		process_checksum(unsigned short *icmp_buffer, \
						int icmphdr_len);
struct timeval		send_echo_request(int fd_socket, \
						struct sockaddr_in *dest_addr, \
						struct icmphdr *icmp, int *sent_pckt);
void				receive_echo_reply(int fd_socket, \
						struct sockaddr_in *dest_addr, \
						struct timeval tv_request, int *received_pckt);
int					create_socket(void);
struct sockaddr_in	initialize_addr(char *addr, char *addr_buf);
struct icmphdr		create_icmp_packet(void);
void				display_reply(struct iphdr *ip_pckt, \
						struct icmphdr *icmp_pckt, \
						struct timeval tv_request, struct timeval tv_reply);
int					check_checksum_reply(struct icmphdr *icmp_pckt);
char				**update_addr_list(char **list, char *new_addr);
void				handler(int signum);
void    			display_ping_stats(int sent_pckt, int received_pckt);

#endif
