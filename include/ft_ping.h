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
# include <termios.h>

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
	int				sent_pckt;
	int				received_pckt;
	suseconds_t	tv_request;
	suseconds_t	tv_reply;
	suseconds_t	tv_min;
	suseconds_t	tv_max;
	suseconds_t	tv_avg;
	suseconds_t	tv_stddev;
	suseconds_t	tv_rtt;
	suseconds_t	*rtt_list;
}	t_ping_stats;

typedef struct s_icmp_pckt
{
	struct icmphdr	icmphdr;
	char			data[ICMP_DATA_SIZE];
}	t_icmp_pckt;

typedef struct s_reply_pckt
{
	struct iphdr	iphdr;
	t_icmp_pckt		icmp_pckt;
}	t_reply_pckt;

typedef struct s_ping
{
	int					send_socket;
	int					recv_socket;
	t_icmp_pckt			icmp_pckt_request;
	t_reply_pckt		reply_pckt;
	struct sockaddr		dest_addr;
	t_ping_stats		stats;
	bool				verbose_mode;
}	t_ping;

int					ft_ping(int argc, char **argv);
void    			run_ping(t_ping *ping, char **argv);
void    			clean_exit(int send_socket, int recv_socket, \
						suseconds_t *rtt_list, int exit_status);

/********************/
/*	   PARSING		*/
/********************/
t_ping				parsing(int argc, char **argv, int *first_addr_index);
t_ping  			initialize_ping_struct(void);

/********************/
/*	   SENDING		*/
/********************/
struct icmphdr		create_icmp_hdr(void);
void				send_echo_request(t_ping *ping);

/********************/
/*	   SOCKETS		*/
/********************/
void				create_sockets(int *send_socket, int *recv_socket);
void    			set_sock_opt(int fd_socket);
void    			close_sockets(int send_socket, int recv_socket);

/********************/
/*	   RECEIVING	*/
/********************/
int					check_checksum_reply(t_icmp_pckt *icmp_pckt);
ssize_t				receive_echo_reply(t_ping *ping);

/********************/
/*	   DISPLAY		*/
/********************/
void				display_reply(t_reply_pckt reply_pckt, t_ping_stats stats);
void    			display_ping_stats(t_ping_stats stats, char *dest_addr_str);
void    			display_transmission_stats(int sent_pckt, \
						int received_pckt, char *dest_addr_str);
void    			display_round_trip_stats(suseconds_t tv_min, \
						suseconds_t tv_max, suseconds_t tv_avg, \
						suseconds_t tv_stddev);
void    			display_invalid_option_and_exit(char *invalid_option);
void    			display_missing_operand_and_exit(void);
void    			display_help_and_exit(void);
void				display_data_sent(char *dest_addr, \
						struct sockaddr_in *dest_addr_struct, \
						bool verbose_mode, u_int16_t echo_request_id);

/********************/
/*		UTILS		*/
/********************/
void    			get_source_ip_addr(char *buffer, unsigned int saddr);
struct sockaddr		get_addr_struct(char *dest_addr);
unsigned short		process_checksum(unsigned short *icmp_pckt);

/********************/
/*	  TIMESTAMPS	*/
/********************/
int					update_timestamps(t_ping_stats *stats);
suseconds_t			get_time_microseconds(struct timeval tv);

/********************/
/*	    SIGNAL		*/
/********************/
void				init_signal_handler(void);

/********************/
/*	    TERMIOS		*/
/********************/
void    			disable_echoctl(void);
void    			restore_termios_config(void);

#endif
