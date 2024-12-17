#include "ft_ping.h"

double	get_time_ms(struct timeval tv)
{
	return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}
