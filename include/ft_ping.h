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
# include <time.h>
# include <math.h>

# define	ICMP_HDR_SIZE	8
# define	ICMP_DATA_SIZE	56
# define	ICMP_PCKT_SIZE	64
# define	IP_HDR_SIZE		20
# define	ONE_SEC			1000000
# define	MAX_IPV4_LEN	16
# define	BUFFER_SIZE		4096

extern bool	g_sigint_triggered;

typedef struct s_ping_stats
{
	int		sent_pckt;
	int		received_pckt;
	double	ts_request;
	double	ts_reply;
	double	ts_min;
	double	ts_max;
	double	ts_avg;
	double	ts_stddev;
	double	ts_rtt;
	double	*rtt_list;
}	t_ping_stats;

typedef struct s_icmp_pckt
{
	struct icmphdr	icmphdr;
	char			data[ICMP_DATA_SIZE];
}	t_icmp_pckt;

typedef struct s_ping
{
	t_icmp_pckt			icmp_pckt;
	struct sockaddr		dest_addr;
	t_ping_stats		stats;
	bool				verbose_mode;
}	t_ping;

int					ft_ping(int argc, char **argv);

/********************/
/*	   PARSING		*/
/********************/
t_ping				parsing(int argc, char **argv, int *first_addr_index);
t_ping  			initialize_ping_struct(void);

/********************/
/*	   SENDING		*/
/********************/
struct icmphdr		create_icmp_hdr(void);
int					create_socket(void);
void				send_echo_request(int fd_socket, t_ping *ping);

/********************/
/*	   RECEIVING	*/
/********************/
int					check_checksum_reply(struct icmphdr *icmp_pckt);
void				receive_echo_reply(int fd_socket, t_ping *ping);

/********************/
/*	   DISPLAY		*/
/********************/
void				display_reply(struct iphdr *ip_pckt, int icmp_seq, \
						t_ping_stats stats);
void    			display_ping_stats(t_ping_stats stats);
void    			display_error_and_exit(void);
void    			display_help_and_exit(void);
void				display_data_sent(char *dest_addr, \
						struct sockaddr_in *dest_addr_struct);

/********************/
/*		UTILS		*/
/********************/
void    			get_source_ip_addr(char *buffer, unsigned int saddr);
struct sockaddr		get_addr_struct(char *dest_addr);
unsigned short		process_checksum(unsigned short *icmp_pckt);

/********************/
/*	  TIMESTAMPS	*/
/********************/
void    			update_timestamps(t_ping_stats *stats);
double   			get_time_ms(struct timeval tv);

/********************/
/*	    SIGNAL		*/
/********************/
void				handler(int signum);

#endif
