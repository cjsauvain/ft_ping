#include "ft_ping.h"

t_sig_enum	g_sig_triggered = NO_SIGNAL;

int	main(int argc, char **argv)
{
	int	status;

	status = ft_ping(argc, argv);
	return status;	
}
