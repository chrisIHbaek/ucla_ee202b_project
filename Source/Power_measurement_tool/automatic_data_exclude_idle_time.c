#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/time.h>

int measure_time(char* program2run) {
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
	snprintf(buf, sizeof(buf), "./'%s'", program2run);

	//Turn off CPU1,2,3
	system("echo 0 > /sys/devices/system/cpu/cpu1/online");
	system("echo 0 > /sys/devices/system/cpu/cpu2/online");
	system("echo 0 > /sys/devices/system/cpu/cpu3/online");

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
	
	return (int)((measure_time - start_time)*1000000); //return execution time in microseconds.
}//end of execution time

int main(int argc, char* argv[]) {
	if (argc != 2) {
		fprintf(stderr, "Wrong number of arguments: %s\n", strerror(errno));
		return 1;	
	}

	char* freq_set[] = {"250MHz", "300MHz", "350MHz", "400MHz", "450MHz", 
			"500MHz", "550MHz", "600MHz", "800MHz", "900MHz",
			"1000MHz", "1.10GHz", "1.20GHz", "1.30GHz", "1.40GHz", "1.50GHz", "1.60GHz"};

	int i; //for loop index
	int run_time; //returned from measure_time()

	for (i=0;i<17;i++) {
		//Measure execution time

		char buf[1024];
		system("cpufreq-set -g userspace");
		snprintf(buf, sizeof(buf), "cpufreq-set -f '%s'", freq_set[i]);
		system(buf);
		//system("cpufreq-info | grep asserted");

		run_time = measure_time(argv[1]);


		//printf("%d\n", run_time);
		char program2run[1024];
		snprintf(program2run, sizeof(program2run), "./power_auto '%s' '%d' '%s'", argv[1], run_time ,freq_set[i]);
		system(program2run);

		char log_file[1024];
		snprintf(log_file, sizeof(log_file), "cp power_model_log.txt power_model_log_%s.txt", freq_set[i]);
		system(log_file);
	}
	return 0;
}
