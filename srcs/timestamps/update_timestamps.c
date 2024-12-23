#include "ft_ping.h"

static struct timeval	get_rtt(struct timeval tv_request, \
								struct timeval tv_reply)
{
	struct timeval	rtt;

	rtt.tv_sec = tv_reply.tv_sec - tv_request.tv_sec;
	rtt.tv_usec = tv_reply.tv_usec - tv_request.tv_usec;
	return rtt;
}

static struct timeval	*update_rtt_list(struct timeval *rtt_list, \
							int received_pckt, struct timeval tv_rtt)
{
	struct timeval	*new_rtt_list;

	new_rtt_list = realloc(rtt_list, (received_pckt + 1) \
					* sizeof(struct timeval));
	if (!new_rtt_list)
	{
		perror("ft_ping: ");
		exit(2);
	}
	new_rtt_list[received_pckt] = tv_rtt;

	return new_rtt_list;
}

static void	get_tv_min_and_max(struct timeval tv_rtt, struct timeval *tv_min, \
								struct timeval *tv_max)
{
	if (!get_time_ms(*tv_min))
		*tv_min = tv_rtt;
	if (!get_time_ms(*tv_max))
		*tv_max = tv_rtt;

	if (get_time_ms(tv_rtt) < get_time_ms(*tv_min))
		*tv_min = tv_rtt;
	else if (get_time_ms(tv_rtt) > get_time_ms(*tv_max))
		*tv_max = tv_rtt;
}

static struct timeval	get_tv_avg(struct timeval tv_avg, \
									struct timeval tv_rtt, int received_pckt)
{
	struct timeval	tv_new_avg;

	tv_new_avg.tv_sec = (tv_avg.tv_sec * received_pckt + tv_rtt.tv_sec) \
							/ (received_pckt + 1);
	tv_new_avg.tv_usec = (tv_avg.tv_usec * received_pckt + tv_rtt.tv_usec) \
							/ (received_pckt + 1);
	return tv_new_avg;
}

static struct timeval	get_tv_stddev(struct timeval *rtt_list, \
									struct timeval tv_avg, int received_pckt)
{
	struct timeval	result;
	int		i;

	if (!received_pckt)
		return tv_avg;
	memset(&result, 0, sizeof(struct timeval));
	i = 0;
	while (i < received_pckt)
	{
		result.tv_sec += pow(rtt_list[i].tv_sec - tv_avg.tv_sec, 2);
		result.tv_usec += pow(rtt_list[i].tv_usec - tv_avg.tv_usec, 2);
		i++;
	}
	result.tv_sec /= received_pckt;
	result.tv_usec /= received_pckt;
	result.tv_sec = sqrt(result.tv_sec);
	result.tv_usec = sqrt(result.tv_usec);

	return result;
}

void	update_timestamps(t_ping_stats *stats)
{
	gettimeofday(&stats->tv_reply, NULL);
	stats->tv_rtt = get_rtt(stats->tv_request, stats->tv_reply);
	stats->rtt_list = update_rtt_list(stats->rtt_list, \
							stats->received_pckt, stats->tv_rtt);
	get_tv_min_and_max(stats->tv_rtt, &stats->tv_min, &stats->tv_max);
	stats->tv_avg = get_tv_avg(stats->tv_avg, stats->tv_rtt, \
						stats->received_pckt);
	stats->tv_stddev = get_tv_stddev(stats->rtt_list, stats->tv_avg, \
						stats->received_pckt);
}
