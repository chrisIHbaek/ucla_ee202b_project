#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <errno.h>
#include <string.h>

int main(int argc, char* argv[]) {
	if (!(argc == 2 || argc == 3)) {
		fprintf(stderr, "Wrong number of arguments: %s\n", strerror(errno));
		return 1;	
	}

//	if (argc == 3 && !!strcmp(argv[2], "-f")){
//		fprintf(stderr, "Wrong option.\n Use -f to show frequencies: %s\n", strerror(errno));
//		return 1;	
//	}

	struct timeval tv;
	time_t start_time_s;
	time_t time_at_measurement_s;
	suseconds_t start_time_u;
	suseconds_t time_at_measurement_u;
	long int execution_time_s;
	long int execution_time_u;
	char freq_val[10];
	int freq_val_int;

	char buf[1024];
	snprintf(buf, sizeof(buf), "./'%s'", argv[1]);

	FILE *f = fopen("execution_time_log.txt", "a");
//	FILE *freq = fopen("/sys/devices/system/cpu/cpu0/cpufreq/scaling_cur_freq", "r");

	gettimeofday(&tv, NULL);
	start_time_s = tv.tv_sec; //seconds since 1970-01-01 00:00 UTC.
	start_time_u = tv.tv_usec; //microseconds since 1970-01-01 00:00 UTC.

	system(buf);
	
	gettimeofday(&tv, NULL);
	time_at_measurement_s = tv.tv_sec;
	time_at_measurement_u = tv.tv_usec;

	double start_second = (double)start_time_s;
	double start_micro = (double)start_time_u / 1000000;
	double start_time = start_second + start_micro;
	double measure_second = (double)time_at_measurement_s;
	double measure_micro = (double)time_at_measurement_u / 1000000;
	double measure_time = measure_second + measure_micro;

//	if (!strcmp(argv[2], "-f")) {
//		fscanf(freq, "%s", freq_val);
//		freq_val_int = atoi(freq_val)/1000;
//		fprintf(f, "%d ", freq_val_int);
//	}

	fprintf(f, "%f\n", measure_time - start_time);
	fclose(f);
//	fclose(freq);
	
	return 0;
}
