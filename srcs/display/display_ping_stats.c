#include "ft_ping.h"

void	display_transmission_stats(int sent_pckt, int received_pckt, char *dest_addr_str)
{
	float	packet_loss;

	packet_loss = ((float)sent_pckt - (float)received_pckt) \
					/ (float)sent_pckt * 100;
	printf("--- %s ping statistics ---\n", dest_addr_str);
	printf("%d packets transmitted, %d packets received, %.0f%% packet loss\n", \
			sent_pckt, received_pckt, packet_loss);
}

void	display_round_trip_stats(suseconds_t tv_min, suseconds_t tv_max, \
									suseconds_t tv_avg, suseconds_t tv_stddev)
{
	printf("round-trip min/avg/max/stddev = ");
	printf("%li.%.03i/", tv_min / 1000, (uint32_t)tv_min % 1000);
	printf("%li.%.03i/", tv_avg / 1000, (uint32_t)tv_avg % 1000);
	printf("%li.%.03i/", tv_max / 1000, (uint32_t)tv_max % 1000);
	printf("%li.%.03i\n", tv_stddev / 1000, (uint32_t)tv_stddev % 1000);
}

void	display_ping_stats(t_ping_stats stats, char *dest_addr_str)
{
	display_transmission_stats(stats.sent_pckt, stats.received_pckt, dest_addr_str);
	display_round_trip_stats(stats.tv_min, stats.tv_max, \
								stats.tv_avg, stats.tv_stddev);
}
