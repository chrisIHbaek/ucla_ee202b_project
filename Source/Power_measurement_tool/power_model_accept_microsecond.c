// ----------------
// For cpu0 only.
// ----------------

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <sys/time.h>

sig_atomic_t volatile isrunning = 1;

//Signal handler
void do_when_interrupted(int sig)
{
	if (sig == SIGINT)
		isrunning = 0;

	puts ("\nStop measuring.\n");
	system("cpufreq-set -g interactive");
	exit(1);
}

int main(int argc, char *argv[])
{
	if (!(argc == 3 || argc ==4)) {
		fprintf(stderr, "Wrong number of arguments: %s\n", strerror(errno));
		return 1;	
	}

	//set the CPU frequency
	if (argc == 4) {
		system("cpufreq-set -g userspace");
		char buf[1024];
		snprintf(buf, sizeof(buf), "cpufreq-set -f '%s'", argv[3]);
		system(buf);
	}

	pid_t pid = fork();

	if (pid == -1) {
		fprintf(stderr, "Cannot fork process: %s\n", strerror(errno));
		return 1;
	}

	else if (pid == 0) {
		// This is run dd that will take sufficient time.
		if(execl(argv[1], argv[1], NULL) == -1) {
			fprintf(stderr, "Cannot run %s: %s\n", argv[1], strerror(errno));
			return 1;
		}
//		if(execl("/home/odroid/Desktop/EE202B_project/power_model_files/matrix", "matrix", NULL) == -1) {
//			fprintf(stderr, "Cannot run dd: %s\n", strerror(errno));
//			return 1;
//		}

		
	} //end of else if

	else {
		signal(SIGINT, &do_when_interrupted); 

		//system("echo Measuring... > power_model_log.txt");

		//Turn off CPU1,2,3
		system("echo 0 > /sys/devices/system/cpu/cpu1/online");
		system("echo 0 > /sys/devices/system/cpu/cpu2/online");
		system("echo 0 > /sys/devices/system/cpu/cpu3/online");

		//enable the sensors
		system("echo 1 > /sys/bus/i2c/drivers/INA231/4-0045/enable");
		system("echo 1 > /sys/bus/i2c/drivers/INA231/4-0040/enable");

    
		int n = 0;
		char a7_v_val[10];
		char a7_w_val[10];
		char a15_v_val[10];
		char a15_w_val[10];
		char freq_val[10];
		int freq_val_int;
		int run_time = (atoi(argv[2]) / 100000); //unit is decisecond
		run_time = run_time - 5; //subtract .5 second from run time.
		if (run_time <= 0){
			fprintf(stderr, "Run time is too short: %s\n", strerror(errno));
			return 1;
		}

		struct timeval tv;
		gettimeofday(&tv, NULL);
		time_t start_time_s = tv.tv_sec; //seconds since 1970-01-01 00:00 UTC.
		time_t time_at_measurement_s;
		suseconds_t start_time_u = tv.tv_usec; //microseconds since 1970-01-01 00:00 UTC.
		suseconds_t time_at_measurement_u;
		
		double start_second = (double)start_time_s;
		double start_micro = (double)start_time_u / 1000000;
		double start_time = start_second + start_micro;
		double measure_time;

		//open power_model_log.txt to write (append).
		FILE *f = fopen("power_model_log.txt", "w");

		if (f == NULL) {
			fprintf(stderr, "Error opening text file!");
			exit(1);
		}

		while(isrunning) {
			//Put timestamp
			gettimeofday(&tv, NULL);
			time_at_measurement_s = tv.tv_sec;
			time_at_measurement_u = tv.tv_usec;
			measure_time = (double)time_at_measurement_s + ((double)time_at_measurement_u / 1000000);
			fprintf(f, "%f ", measure_time - start_time);

			//measure voltage and power
			//open sensor readings (read).
			FILE *freq = fopen("/sys/devices/system/cpu/cpu0/cpufreq/scaling_cur_freq", "r");
			FILE *a7_v = fopen("/sys/bus/i2c/drivers/INA231/4-0045/sensor_V", "r");
			FILE *a7_w = fopen("/sys/bus/i2c/drivers/INA231/4-0045/sensor_W", "r");
			FILE *a15_v = fopen("/sys/bus/i2c/drivers/INA231/4-0040/sensor_V", "r");
			FILE *a15_w = fopen("/sys/bus/i2c/drivers/INA231/4-0040/sensor_W", "r");
			if (freq == NULL || a7_v == NULL || a7_w == NULL || a15_v == NULL || a15_w == NULL) {
				fprintf(stderr, "Error opening sensor data!");
				exit(1);
			}
			
			//fprintf(f, "CPU (cpu0) frequency(MHz): ");
			fscanf(freq, "%s", freq_val);
			freq_val_int = atoi(freq_val)/1000;
			fprintf(f, "%d ", freq_val_int);

			//fprintf(f, "A7 voltage(V), power(W): ");
			fscanf(a7_v, "%s", a7_v_val);
			fscanf(a7_w, "%s", a7_w_val);
			fprintf(f, "%s %s ", a7_v_val, a7_w_val);

			//fprintf(f, "A15 voltage(V), power(W): ");
			fscanf(a15_v, "%s", a15_v_val);
			fscanf(a15_w, "%s", a15_w_val);
			fprintf(f, "%s %s \n", a15_v_val, a15_w_val);

			fclose(freq);
			fclose(a7_v);
			fclose(a7_w); 
			fclose(a15_v);
			fclose(a15_w);						
		
			if (n == run_time) 
				isrunning = 0;

			n++;
			usleep(100*1000); //sleep for 0.1 seconds
			//measure CPU frequency
		} //end of while loop
		printf("I'm outside the loop!\n");	
		fclose(f);
		if (argc == 4)		
			system("cpufreq-set -g interactive");
	} //end of else
		
	return 0;
}
