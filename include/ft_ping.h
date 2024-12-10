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

# define	ICMP_HDR_SIZE	8
# define	ICMP_DATA_SIZE	56
# define	ICMP_PCKT_SIZE	64
# define	IP_HDR_SIZE		20
# define	ONE_SEC			1000000
# define	MAX_IPV4_LEN	16

extern bool	g_sigint_triggered;

typedef struct s_ping_stats
{
	int	sent_pckt;
	int	received_pckt;
}	t_ping_stats;

typedef struct s_icmp_pckt
{
	struct icmphdr	icmphdr;
	char			data[ICMP_DATA_SIZE];
}	t_icmp_pckt;

typedef struct s_ping
{
	t_icmp_pckt			icmp_pckt;
	struct sockaddr_in	*dest_addr_list;
	int					dest_addr_count;
	struct timeval		tv_sent;
	t_ping_stats		stats;
	bool				verbose_mode;
}	t_ping;

t_ping				parsing(int argc, char **argv);
int					ft_ping(int argc, char **argv);
unsigned short		process_checksum(unsigned short *icmp_pckt);
void				send_echo_request(int fd_socket, t_ping *ping, \
										int addr_index);
void				receive_echo_reply(int fd_socket, t_ping *ping, \
										int addr_index);
int					create_socket(void);
struct icmphdr		create_icmp_hdr(void);
int					check_checksum_reply(struct icmphdr *icmp_pckt);
struct sockaddr_in	*update_addr_list(char **argv, int addr_count);
void				handler(int signum);

/** Display **/
void				display_reply(struct iphdr *ip_pckt, \
						struct icmphdr *icmp_pckt, \
						struct timeval tv_request, struct timeval tv_reply);
void    			display_ping_stats(int sent_pckt, int received_pckt);
void    			display_error_and_exit(void);
void    			display_help_and_exit(void);
void				display_data_sent(struct sockaddr_in dest_addr, \
										size_t icmp_pckt_size);

#endif
