#include "ft_ping.h"

void	display_error_and_exit(void)
{
	fprintf(stderr, "ft_ping: missing host operand\n");
	fprintf(stderr, "Try 'ping -?' for more information.\n");
	exit(64);
}

void	display_help_and_exit(void)
{
	printf("Usage: ping [OPTION...] HOST ...\n");
	printf("Send ICMP ECHO_REQUEST packets to network hosts.\n\n");
	printf(" Options valid for all request types:\n");
	printf("  -v, --verbose              verbose output\n\n");
	printf(" Options valid for --echo requests:\n");
	printf("  -?, --help                 give this help list\n\n");
	exit(0);
}
