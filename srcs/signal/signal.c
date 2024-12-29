#include "ft_ping.h"

static void	handler(int signum)
{
	g_sigint_triggered = true;
	restore_termios_config();
	(void)signum;
}

void	init_signal_handler(void)
{
	if (signal(SIGINT, handler) == SIG_ERR)
	{
		perror("ft_ping");
		exit(1);
	}
}
