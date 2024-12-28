#include "ft_ping.h"

suseconds_t	get_time_microseconds(struct timeval tv)
{
	return tv.tv_sec * 1000000 + tv.tv_usec;
}
