#include "ft_ping.h"

void	get_redirect_message(char *icmp_message, u_int8_t code)
{
	if (code == 0)
		strcpy(icmp_message, "Redirect datagrams for the Network");
	if (code == 1)
		strcpy(icmp_message, "Redirect datagrams for the Host");
	if (code == 2)
		strcpy(icmp_message, "Redirect datagrams for the Type of Service and Network");
	if (code == 3)
		strcpy(icmp_message, "Redirect datagrams for the Type of Service and Host");
}
