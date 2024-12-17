#include "ft_ping.h"

static double	get_rtt(double ts_request, double ts_reply)
{
	return ts_reply - ts_request;
}

static double	*update_rtt_list(double *rtt_list, int received_pckt, double ts_rtt)
{
	double	*new_rtt_list;
	new_rtt_list = realloc(rtt_list, (received_pckt + 1) * sizeof(double));
	if (!new_rtt_list)
	{
		perror("ft_ping: ");
		exit(2);
	}
	new_rtt_list[received_pckt] = ts_rtt;

	return new_rtt_list;
}

static void	get_ts_min_and_max(double ts_rtt, double *ts_min, double *ts_max)
{
	if (!*ts_min)
		*ts_min = ts_rtt;
	if (!*ts_max)
		*ts_max = ts_rtt;

	if (ts_rtt < *ts_min)
		*ts_min = ts_rtt;
	else if (ts_rtt > *ts_max)
		*ts_max = ts_rtt;
}

static double	get_ts_avg(double ts_avg, double ts_rtt, int received_pckt)
{
	return ((ts_avg * received_pckt + ts_rtt) / (received_pckt + 1));
}

static double	get_ts_stddev(double *rtt_list, double ts_avg, int received_pckt)
{
	double	result;
	int		i;

	if (!received_pckt)
		return ts_avg;
	result = 0;
	i = 0;
	while (i < received_pckt)
	{
		result += pow(rtt_list[i] - ts_avg, 2.0);
		i++;
	}
	result /= received_pckt;
	result = sqrt(result);

	return result;
}

void	update_timestamps(t_ping_stats *stats)
{
	struct timeval	tv_reply;

	gettimeofday(&tv_reply, NULL);
	stats->ts_reply = get_time_ms(tv_reply);
	stats->ts_rtt = get_rtt(stats->ts_request, stats->ts_reply);
	stats->rtt_list = update_rtt_list(stats->rtt_list, \
							stats->received_pckt, stats->ts_rtt);
	get_ts_min_and_max(stats->ts_rtt, &stats->ts_min, &stats->ts_max);
	stats->ts_avg = get_ts_avg(stats->ts_avg, stats->ts_rtt, \
						stats->received_pckt);
	stats->ts_stddev = get_ts_stddev(stats->rtt_list, stats->ts_avg, \
						stats->received_pckt);
}
