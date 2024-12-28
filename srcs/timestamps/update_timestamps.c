#include "ft_ping.h"

static suseconds_t	get_rtt(suseconds_t tv_request, suseconds_t tv_reply)
{
	return tv_reply - tv_request;
}

static suseconds_t	*update_rtt_list(suseconds_t *rtt_list, \
							int received_pckt, suseconds_t tv_rtt)
{
	suseconds_t	*new_rtt_list;

	new_rtt_list = realloc(rtt_list, (received_pckt + 1) \
					* sizeof(suseconds_t));
	if (!new_rtt_list)
		return NULL;
	new_rtt_list[received_pckt] = tv_rtt;

	return new_rtt_list;
}

static void	get_tv_min_and_max(suseconds_t tv_rtt, suseconds_t *tv_min, \
								suseconds_t *tv_max)
{
	if (!*tv_min || tv_rtt < *tv_min)
		*tv_min = tv_rtt;
	if (tv_rtt > *tv_max)
		*tv_max = tv_rtt;
}

static suseconds_t	get_tv_avg(suseconds_t tv_avg, suseconds_t tv_rtt, \
								int received_pckt)
{
	return ((tv_avg * received_pckt + tv_rtt) / (received_pckt + 1));
}

static suseconds_t	get_tv_stddev(suseconds_t *rtt_list, suseconds_t tv_avg, \
									int received_pckt)
{
	suseconds_t	result;
	int			i;

	if (!received_pckt)
		return tv_avg;
	result = 0;
	i = 0;
	while (i < received_pckt)
	{
		result += pow(rtt_list[i] - tv_avg, 2);
		i++;
	}
	result /= received_pckt;
	result = sqrt(result);

	return result;
}

static suseconds_t	get_tv_reply(void)
{
	struct timeval	tv_reply;
	suseconds_t		time;

	if (gettimeofday(&tv_reply, NULL) == -1)
		return -1;
	time = get_time_microseconds(tv_reply);

	return time;
}

int	update_timestamps(t_ping_stats *stats)
{
	stats->tv_reply = get_tv_reply();
	if (stats->tv_reply == -1)
		return -1;
	stats->tv_rtt = get_rtt(stats->tv_request, stats->tv_reply);
	stats->rtt_list = update_rtt_list(stats->rtt_list, \
							stats->received_pckt, stats->tv_rtt);
	if (!stats->rtt_list)
		return -2;
	get_tv_min_and_max(stats->tv_rtt, &stats->tv_min, &stats->tv_max);
	stats->tv_avg = get_tv_avg(stats->tv_avg, stats->tv_rtt, \
						stats->received_pckt);
	stats->tv_stddev = get_tv_stddev(stats->rtt_list, stats->tv_avg, \
						stats->received_pckt);
	return 0;
}
