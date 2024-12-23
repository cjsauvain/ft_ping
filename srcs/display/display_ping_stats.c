#include "ft_ping.h"

void	display_ping_stats(t_ping_stats stats)
{
	float	packet_loss;

	packet_loss = ((float)stats.sent_pckt - (float)stats.received_pckt) \
					/ (float)stats.sent_pckt * 100;
	printf("--- localhost ping statistics ---\n");
	printf("%d packets transmitted, %d packets received, %.0f%% packet loss\n", \
			stats.sent_pckt, stats.received_pckt, packet_loss);
	printf("round-trip min/avg/max/stddev = ");
	printf("%.03f/%.03f/%.03f/%.03f ms\n", get_time_ms(stats.tv_min), \
			get_time_ms(stats.tv_avg), get_time_ms(stats.tv_max), \
			get_time_ms(stats.tv_stddev));
}
