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

	//char buf[1024];
	//snprintf(buf, sizeof(buf), "./'%s'", program2run);

	FILE *f = fopen("execution_time_log.txt", "a");

	gettimeofday(&tv, NULL);
	start_time_s = tv.tv_sec; //seconds since 1970-01-01 00:00 UTC.
	start_time_u = tv.tv_usec; //microseconds since 1970-01-01 00:00 UTC.

	system(program2run);
	
	gettimeofday(&tv, NULL);
	time_at_measurement_s = tv.tv_sec;
	time_at_measurement_u = tv.tv_usec;

	double start_second = (double)start_time_s;
	double start_micro = (double)start_time_u / 1000000;
	double start_time = start_second + start_micro;
	double measure_second = (double)time_at_measurement_s;
	double measure_micro = (double)time_at_measurement_u / 1000000;
	double measure_time = measure_second + measure_micro;

	fprintf(f, "%f\n", measure_time - start_time);
	//fprintf(f2, "%d\n", (int)((measure_time - start_time)*1000000)); //the unit is microsecond.
	fclose(f);
	
	return (int)((measure_time - start_time)*1000000); //return execution time in microseconds.
}//end of execution time

int main(int argc, char* argv[]) {
	char* freq_set[] = {"250MHz", "300MHz", "350MHz", "400MHz", "450MHz", 
			"500MHz", "550MHz", "600MHz", "800MHz", "900MHz",
			"1000MHz", "1.10GHz", "1.20GHz", "1.30GHz", "1.40GHz", "1.50GHz", "1.60GHz"};

	int i; //for loop index
	int run_time; //returned from measure_time()
	char program2run[1024];

	if (argc != 3) {
		fprintf(stderr, "Wrong number of arguments!");
		exit(1);
	}
	
	FILE* f = fopen("execution_time_log.txt","w");
	if (f == NULL) {
		fprintf(stderr, "Error opening txt file!");
		exit(1);
	}
	fclose(f);
		
	//Turn off CPU1,2,3
	system("echo 0 > /sys/devices/system/cpu/cpu1/online");
	system("echo 0 > /sys/devices/system/cpu/cpu2/online");
	system("echo 0 > /sys/devices/system/cpu/cpu3/online");

	for (i=0;i<17;i++) {
		//Measure execution time

		char buf[1024];
		system("cpufreq-set -g userspace");
		snprintf(buf, sizeof(buf), "cpufreq-set -f '%s'", freq_set[i]);
		system(buf);
		//system("cpufreq-info | grep asserted");
	
		snprintf(program2run, sizeof(program2run), "./'%s' '%s'", argv[1], argv[2]);

		run_time = measure_time(program2run);
		printf("Measurement done for %s\n", freq_set[i]);
	}

	//Copy the execution_time_log.txt
	char cp_command[1024];
	snprintf(cp_command, sizeof(cp_command), "cp execution_time_log.txt time_log_%s_%s", argv[1], argv[2]);
	system(cp_command);
	
	printf("\n\n\n===================\n");
	printf("Measurement finished.\n");
	return 0;
}
