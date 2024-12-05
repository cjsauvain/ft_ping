#include "ft_ping.h"

void	display_ping_stats(int sent_pckt, int received_pckt)
{
	float	packet_loss;

	packet_loss = ((float)sent_pckt - (float)received_pckt) \
					/ (float)sent_pckt * 100;
	printf("--- localhost ping statistics ---\n");
	printf("%d packets transmitted, %d packets received, %.0f%% packet loss\n", \
			sent_pckt, received_pckt, packet_loss);
	printf("A FAIREround-trip min/avg/max/stddev = 0,052/0,052/0,052/0,000 ms\n");
}
