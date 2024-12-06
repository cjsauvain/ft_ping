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

	memset(ping.icmp_pckt, 0, ICMP_HDR_SIZE);
	ping.dest_addr_list = NULL;
	ping.stats.sent_pckt = 0;
	ping.stats.received_pckt = 0;
	memset(ping.data, 0, ICMP_DATA_SIZE);
	ping.verbose_mode = false;

	return ping;
}

t_ping	parsing(int argc, char **argv)
{
	t_ping	ping;
	int		i;
	int		addr_count;

	if (argc == 1)// check for ip/hostname too
		display_error_message();
	ping = initialize_ping_struct();
	i = 1;
	addr_count = 0;
	while (argv[i])
	{
		if (argv[i][0] == '-' && argv[i][1] == '?')
			display_help_and_exit();
		else if (argv[i][0] == '-')
			get_ping_opt(&ping, argv[i]);
		else
			addr_count++;
		i++;
	}
	if (!addr_count)
		display_error_and_exit();
	ping.dest_addr_list = update_addr_list(argv[i], addr_count);
	ping.dest_addr_list[addr_count] = NULL;
	return ping;
}
