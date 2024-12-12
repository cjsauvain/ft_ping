#include "ft_ping.h"

static void	get_ping_opt(t_ping *ping, char *opt)
{
	int	i = 1;

	ping->verbose_mode = false;
	while (opt[i])
	{
		if (opt[i] != 'v')
			display_error_and_exit();
		else
			ping->verbose_mode = true;
		i++;
	}
}

static t_ping	initialize_ping_struct(void)
{
	t_ping	ping;

	memset(&ping.icmp_pckt, 0, ICMP_HDR_SIZE + ICMP_DATA_SIZE);
	memset(&ping.dest_addr, 0, sizeof(ping.dest_addr));
	ping.stats.sent_pckt = 0;
	ping.stats.received_pckt = 0;
	ping.verbose_mode = false;

	return ping;
}

t_ping	parsing(int argc, char **argv, int *first_addr_index)
{
	t_ping	ping;
	int		i;

	if (argc == 1)
		display_error_and_exit();
	ping = initialize_ping_struct();
	i = 1;
	while (argv[i])
	{
		if (argv[i][0] == '-' && argv[i][1] == '?')
			display_help_and_exit();
		else if (argv[i][0] == '-')
			get_ping_opt(&ping, argv[i]);
		else if (!*first_addr_index)
			*first_addr_index = i;
		i++;
	}
	if (!first_addr_index)
		display_error_and_exit();
	return ping;
}
