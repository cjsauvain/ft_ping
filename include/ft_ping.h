#ifndef FT_PING_H
# define FT_PING_H

# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/socket.h>
# include <netinet/ip_icmp.h>
# include <arpa/inet.h>

typedef struct s_command {
	int		status;
	char	*ip_addr;
	char	option[2];
}	t_command;

t_command	parsing(int argc, char **argv);
int			ft_ping(t_command command);

#endif
