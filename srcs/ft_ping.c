#include "ft_ping.h"

int	ft_ping(int argc, char **argv)
{
	t_ping	ping;
	int		first_addr_index;

	first_addr_index = 0;
	disable_echoctl();
	init_signal_handler();
	ping = parsing(argc, argv, &first_addr_index);
	argv += first_addr_index;
	run_ping(&ping, argv);
	return ping.exit_status;
}
