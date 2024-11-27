#ifndef FT_PING_H
# define FT_PING_H

# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/socket.h>
#include <linux/icmp.h>
# include <arpa/inet.h>

typedef struct s_command {
	int		status;
	char	*ip_addr;
	char	option[2];
}	t_command;

t_command			parsing(int argc, char **argv);
int					ft_ping(t_command command);
unsigned short		process_checksum(unsigned short *icmp_buffer, int icmphdr_len);
void				send_echo_request(int fd_socket, struct sockaddr_in *dest_addr, struct icmphdr *icmp);
void				receive_echo_reply(int fd_socket, struct sockaddr_in *dest_addr);
int					create_socket(void);
struct sockaddr_in	initialize_addr(char *ip_addr);
struct icmphdr		create_icmp_packet(void);

#endif
