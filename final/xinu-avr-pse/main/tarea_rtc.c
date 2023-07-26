#include <xinu.h>

extern unsigned long rtc_miliseconds;

int rtc(void)
{
	while(1) {
        rtc_miliseconds++;
		sleepms(1);
	}
}
