#include "ft_ping.h"

void	close_sockets(int send_socket, int recv_socket)
{
	close(send_socket);
	close(recv_socket);
}
