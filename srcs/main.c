#include "ft_ping.h"

bool	g_sigint_triggered = false;

int	main(int argc, char **argv)
{
	int	status;

	status = ft_ping(argc, argv);
	return status;	
}
