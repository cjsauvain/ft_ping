#include "ft_ping.h"

void	handler(int signum)
{
	g_sigint_triggered = true;
	(void)signum;
}
