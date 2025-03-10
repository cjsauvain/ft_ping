#include "ft_ping.h"

void	display_invalid_option_and_exit(char *invalid_option)
{
	fprintf(stderr, "ft_ping: invalid option -- '%s'\n", invalid_option);
	fprintf(stderr, "Try 'ping -?' for more information.\n");
	exit(64);
}

void	display_missing_operand_and_exit(void)
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
	printf("  -v	verbose output\n\n");
	printf(" Options valid for --echo requests:\n");
	printf("  -?	give this help list\n\n");
	exit(0);
}
