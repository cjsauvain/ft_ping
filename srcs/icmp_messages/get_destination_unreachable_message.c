#include "ft_ping.h"

static void	RFC_792_codes(char *icmp_message, u_int8_t code)
{
	if (code == 0)
		strcpy(icmp_message, "Destination Net Unreachable");
	if (code == 1)
		strcpy(icmp_message, "Destination Host Unreachable");
	if (code == 2)
		strcpy(icmp_message, "Destination Protocol Unreachable");
	if (code == 3)
		strcpy(icmp_message, "Destination Port Unreachable");
	if (code == 4)
		strcpy(icmp_message, "Destination Fragmentation Needed and Don't Fragment was Set");
	if (code == 5)
		strcpy(icmp_message, "Destination Source Route Failed");
}

static void	RFC_1122_codes(char *icmp_message, u_int8_t code)
{
	if (code == 6)
		strcpy(icmp_message, "Destination Network Unknown");
	if (code == 7)
		strcpy(icmp_message, "Destination Host Unknown");
	if (code == 8)
		strcpy(icmp_message, "Source Host Isolated");
	if (code == 9)
		strcpy(icmp_message, "Communication with Destination Network is Administratively Prohibited");
	if (code == 10)
		strcpy(icmp_message, "Communication with Destination Host is Administratively Prohibited");
	if (code == 11)
		strcpy(icmp_message, "Destination Network Unreachable for Type of Service");
	if (code == 12)
		strcpy(icmp_message, "Destination Host Unreachable for Type of Service");
}

static void	RFC_1812_codes(char *icmp_message, u_int8_t code)
{
	if (code == 13)
		strcpy(icmp_message, "Communication Administratively Prohibited");
	if (code == 14)
		strcpy(icmp_message, "Host Precedence Violation");
	if (code == 15)
		strcpy(icmp_message, "Precedence cutoff in effect");
}

void	get_destination_unreachable_message(char *icmp_message, u_int8_t code)
{
	RFC_792_codes(icmp_message, code);
	RFC_1122_codes(icmp_message, code);
	RFC_1812_codes(icmp_message, code);
}
