#include <stdio.h>
#include "Dusk2Dawn.h"
#include <time.h>

// note to self 2019.03.06: THIS REALLY WORKS!!! TESTED.
// source: https://github.com/dmkishi/Dusk2Dawn

Dusk2Dawn budapest(47.50,19.10,1);

#define DST 0
int sunrise = budapest.sunrise(2019, 11, 28, DST);
int sunrisehour = sunrise / 60;
int sunrisemin = sunrise % 60;
int sunset = budapest.sunset(2019, 11, 28, DST);
int sunsethour = sunset / 60;
int sunsetmin = sunset % 60;

// ------------------------------

time_t t = time(NULL);
struct tm tm = *localtime(&t);

#define DST 0
int sunrise_now = budapest.sunrise(tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, DST);
int sunset_now = budapest.sunset(tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, DST);

int main()
{
	printf("now: %d.%02d.%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1,
			tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

	printf("sunrise %02d:%02d\n", sunrise_now/60, sunrise_now % 60);
	printf("sunset  %02d:%02d\n", sunset_now/60, sunset_now % 60);
	printf("DST: %d\n", DST);
	return 0;
}
