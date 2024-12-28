#include "ft_ping.h"

void	clean_exit(int send_socket, int recv_socket, suseconds_t *rtt_list, \
					int exit_status)
{
	perror("ft_ping");
	close_sockets(send_socket, recv_socket);
	free(rtt_list);
	exit(exit_status);
}
