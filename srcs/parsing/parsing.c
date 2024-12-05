#include "ft_ping.h"

static void	display_error_message(void)
{
	fprintf(stderr, "ft_ping: missing host operand\n");
	fprintf(stderr, "Try 'ping -?' for more information.\n");
	exit(64);
}

static void	display_help(void)
{
	printf("Usage: ping [OPTION...] HOST ...\n");
	printf("Send ICMP ECHO_REQUEST packets to network hosts.\n\n");
	printf(" Options valid for all request types:\n");
	printf("  -v, --verbose              verbose output\n\n");
	printf(" Options valid for --echo requests:\n");
	printf("  -?, --help                 give this help list\n\n");
	exit(0);
}

static void	get_ping_opt(t_ping *ping, char *opt)
{
	int	i = 1;

	ping->verbose_mode = false;
	while (opt[i])
	{
		if (opt[i] != 'v')
			display_error_message();
		else
			ping->verbose_mode = true;
		i++;
	}
}

static t_ping	initialize_ping_struct(void)
{
	t_ping	ping;

	ping.addr = NULL;
	memset(ping.addr_buf, 0, MAX_IPV4_LEN);
	ping.verbose_mode = false;
	ping.sent_pckt = 0;
	ping.received_pckt = 0;

	return ping;
}

t_ping	parsing(int argc, char **argv)
{
	t_ping	ping;
	int			i;

	if (argc == 1)
		display_error_message();
	ping = initialize_ping_struct();
	i = 1;
	while (argv[i])
	{
		if (argv[i][0] == '-' && argv[i][1] == '?')
			display_help();
		else if (argv[i][0] == '-')
			get_ping_opt(&ping, argv[i]);
		else
			ping.addr = update_addr_list(ping.addr, argv[i]);
		i++;
	}
	return ping;
}
