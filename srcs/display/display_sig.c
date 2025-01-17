#include "ft_ping.h"

void	display_sig(void)
{
	if (g_sig_triggered == SIG_INT)
		printf("^C");
	else if (g_sig_triggered == SIG_QUIT)
		printf("^\\Quit");
}
