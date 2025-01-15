#include "ft_ping.h"

void	get_parameter_problem_message(char *icmp_message, u_int8_t code)
{
	if (code == 0)
		strcpy(icmp_message, "Pointer indicates the error");
	if (code == 1)
		strcpy(icmp_message, "Missing a Required Option");
	if (code == 2)
		strcpy(icmp_message, "Bad Length");
}
