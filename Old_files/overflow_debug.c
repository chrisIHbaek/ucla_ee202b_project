#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int main() {
	struct timeval tv;
	while (1){
		gettimeofday(&tv, NULL);
		time_t start_time_s = tv.tv_sec; //seconds since 1970-01-01 00:00 UTC.
		time_t time_at_measurement_s;
		suseconds_t start_time_u = tv.tv_usec; //microseconds since 1970-01-01 00:00 UTC.
		double seconds = (double)start_time_s;
		double micro_s = (double)start_time_u / 1000000;
		double time = (double)start_time_s + micro_s;
		printf("%f seconds ", time);
		printf("\n");
	}
	return 0;
}
