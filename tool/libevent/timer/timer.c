#include <stdio.h>
#include <event.h>

void onTime(int sock, short event, void *arg) {
	printf("Game Over!\n");

	struct timeval tv;
	tv.tv_sec = 1;
	tv.tv_usec = 0;
	event_add((struct event *)arg, &tv);
}

int main()
{
	event_init();
	struct event evTime;
	evtimer_set(&evTime, onTime, &evTime); // the 3rd argment is for function onTime.

	struct timeval tv;
	tv.tv_sec = 1;
	tv.tv_usec = 0;

	event_add(&evTime, &tv);
	event_dispatch();

	return 0;
}
