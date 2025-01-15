#include "ft_ping.h"

void	get_time_exceeded_message(char *icmp_message, u_int8_t code)
{
	if (code == 0)
		strcat(icmp_message, "Time to Live exceeded in Transit");
	if (code == 1)
		strcat(icmp_message, "Fragment Reassembly Time Exceeded");
}
