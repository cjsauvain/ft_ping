#include "ft_ping.h"

static void	handler(int signum)
{
	if (signum == SIGINT)
		g_sig_triggered = SIG_INT;
	else
		g_sig_triggered = SIG_QUIT;
}

void	init_signal_handler(void)
{
	if (signal(SIGINT, handler) == SIG_ERR)
	{
		perror("ft_ping");
		exit(1);
	}
	if (signal(SIGQUIT, handler) == SIG_ERR)
	{
		perror("ft_ping");
		exit(1);
	}
}
