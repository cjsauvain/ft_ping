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
	printf("%li,%.03i/", stats.tv_min / 1000, (uint32_t)stats.tv_min % 1000);
	printf("%li,%.03i/", stats.tv_avg / 1000, (uint32_t)stats.tv_avg % 1000);
	printf("%li,%.03i/", stats.tv_max / 1000, (uint32_t)stats.tv_max % 1000);
	printf("%li,%.03i\n", stats.tv_stddev / 1000, (uint32_t)stats.tv_stddev % 1000);
}
