#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <sys/time.h>

sig_atomic_t volatile isrunning = 1;

char freq_val[10];
int freq;
char a7_w_val[10];
char a15_w_val[10];

//Signal handler
void do_when_interrupted(int sig)
{
	if (sig == SIGINT)
		isrunning = 0;

	puts ("\nStop measuring.\n");
	system("cpufreq-set -g interactive");
	exit(1);
}

int main(int argc, char* argv[]) {
	FILE *file_freq;
	FILE *file_a7_w;
	FILE *file_a15_w;
	int freq_val_int;
	double energy_sum = 0;
	
	struct timeval tv;
	time_t start_time_s;
	time_t time_at_measurement_s;
	suseconds_t start_time_u;
	suseconds_t time_at_measurement_u;
	long int execution_time_s;
	long int execution_time_u;

	signal(SIGINT, &do_when_interrupted);  //To stop the loop with ctr + C

	if (argc == 1) {
		printf("Default governor(Interactive) is selected!\n");
		system("cpufreq-set -g interactive");
	}
	else if (argc == 2) {
		char governor[1024];
		snprintf(governor, sizeof(governor), "cpufreq-set -g %s", argv[1]);
		system(governor);
	}
	else if (argc == 3) {
		if (strcmp(argv[1],"userspace")) {
			fprintf(stderr, "Only userspace governor allows manual scaling: %s\n", strerror(errno));
			return 1;
		}
		char governor[1024];
		snprintf(governor, sizeof(governor), "cpufreq-set -g %s", argv[1]);
		system(governor);
		
		char set_freq[1024];
		snprintf(set_freq, sizeof(set_freq), "cpufreq-set -f %s", argv[2]);
		system(set_freq);
	}
	else {
		fprintf(stderr, "Wrong number of arguments: %s\n", strerror(errno));
		return 1;	
	}
	//Turn off CPU1,2,3
	system("echo 0 > /sys/devices/system/cpu/cpu1/online");
	system("echo 0 > /sys/devices/system/cpu/cpu2/online");
	system("echo 0 > /sys/devices/system/cpu/cpu3/online");

	//enable the sensors
	system("echo 1 > /sys/bus/i2c/drivers/INA231/4-0045/enable");
	system("echo 1 > /sys/bus/i2c/drivers/INA231/4-0040/enable");

	gettimeofday(&tv, NULL);
	start_time_s = tv.tv_sec; //seconds since 1970-01-01 00:00 UTC.
	start_time_u = tv.tv_usec; //microseconds since 1970-01-01 00:00 UTC.
	
	while(isrunning) {
		gettimeofday(&tv, NULL);
		time_at_measurement_s = tv.tv_sec;
		time_at_measurement_u = tv.tv_usec;

		double start_second = (double)start_time_s;
		double start_micro = (double)start_time_u / 1000000;
		double start_time = start_second + start_micro;
		double measure_second = (double)time_at_measurement_s;
		double measure_micro = (double)time_at_measurement_u / 1000000;
		double measure_time = measure_second + measure_micro;

		printf("Elapsed Time: %f\t", measure_time - start_time);

		//open sensor readings (read).
		file_freq = fopen("/sys/devices/system/cpu/cpu0/cpufreq/scaling_cur_freq", "r");
		file_a7_w = fopen("/sys/bus/i2c/drivers/INA231/4-0045/sensor_W", "r");
		file_a15_w = fopen("/sys/bus/i2c/drivers/INA231/4-0040/sensor_W", "r");
		if (file_freq == NULL || file_a7_w == NULL || file_a15_w == NULL) {
			fprintf(stderr, "Error opening sensor data!");
			exit(1);
		}
		fscanf(file_freq, "%s", freq_val);
		freq_val_int = atoi(freq_val)/1000;

		if (freq_val_int >= 800) {//Big CPU
			fscanf(file_a15_w, "%s", a15_w_val);
			printf("Big CPU: %sW\t", a15_w_val);
			energy_sum += atof(a15_w_val);
		}

		else {//Little CPU
			fscanf(file_a7_w, "%s", a7_w_val);
			energy_sum += atof(a7_w_val);
			printf("Little CPU: %sW\t", a7_w_val);
		}
		fclose(file_freq);
		fclose(file_a7_w); 
		fclose(file_a15_w);						

		//usleep(100*1000); //sleep for 0.1 seconds
		sleep(1);
		printf("Energy: %f Watt-second for %dMHz\n", energy_sum, freq_val_int);
	}//end of while loop
	return 0;
}

	

