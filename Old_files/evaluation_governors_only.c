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

double compare_governors();

//Signal handler
void do_when_interrupted(int sig)
{
	if (sig == SIGINT)
		isrunning = 0;

	puts ("\nStop measuring.\n");
	system("cpufreq-set -g interactive");
	exit(1);
}

int main(int arc, char* argv[]) {
	//Turn off CPU1,2,3
	system("echo 0 > /sys/devices/system/cpu/cpu1/online");
	system("echo 0 > /sys/devices/system/cpu/cpu2/online");
	system("echo 0 > /sys/devices/system/cpu/cpu3/online");

	if (arc != 3) {
		fprintf(stderr, "Wrong number arguments: %s\n", strerror(errno));
		return 1;	
	}

	int matrix_size = atoi(argv[1]);

	if (!strcmp(argv[2], "-g")) { //comparison of governors enabled
		double energy_returned;
		printf("\n\n==================================\n");
		printf("Now cpufreq governors are compared...\n");
		printf("Ondemand governor is not evaluated.\n");		
		
		system("cpufreq-set -g powersave");
		energy_returned = compare_governors(argv[1]);
		printf("Interactive governor: ");
		//printf("Interactive governor: %f Watt-second\n", energy_returned);
/*
		system("cpufreq-set -g conservative");
		energy_returned = compare_governors(argv[1]);
		printf("Conservative governor: %f Watt-second\n", energy_returned);

		system("cpufreq-set -g powersave");
		energy_returned = compare_governors(argv[1]);
		printf("Powersave governor: %f Watt-second\n", energy_returned);

		system("cpufreq-set -g performance");
		energy_returned = compare_governors(argv[1]);
		printf("Performance governor: %f Watt-second\n", energy_returned);

		system("cpufreq-set -g userspace");
		energy_returned = compare_governors(argv[1]);
		printf("Userspace governor with suggested frequency: %f Watt-second\n", energy_returned);
*/	
	}

	//Continue on the real-time frequency scaling!!
	return 0;
}

double compare_governors(char* matrix_size) {
	double energy_sum = 0;
	pid_t pid = fork();

	if (pid == -1) {
		fprintf(stderr, "Cannot fork process: %s\n", strerror(errno));
		return 1;
	}

	else if (pid == 0) {
		FILE *file_freq;
		FILE *file_a7_w;
		FILE *file_a15_w;
		int freq_val_int;
		int status;
		struct timeval tv;
		time_t start_time_s;
		time_t time_at_measurement_s;
		suseconds_t start_time_u;
		suseconds_t time_at_measurement_u;
		long int execution_time_s;
		long int execution_time_u;

		signal(SIGINT, &do_when_interrupted);  //To stop the loop with ctr + C

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
				energy_sum += 0.1 * atof(a15_w_val);
			}

			else {//Little CPU
				fscanf(file_a7_w, "%s", a7_w_val);
				energy_sum += 0.1 * atof(a7_w_val);
				printf("Little CPU: %sW\t", a7_w_val);
			}
			fclose(file_freq);
			fclose(file_a7_w); 
			fclose(file_a15_w);						

			usleep(100*1000); //sleep for 0.1 seconds
			printf("energy sum: %f for %dMHz\n", energy_sum, freq_val_int);
		} //end of while loop
		printf("End of loop\n");
		printf("%f Watt-second\n", energy_sum);
		return energy_sum;
	}//end of else if(child process)

	else  { //parent process
		char cmd_buf[1024];
		snprintf(cmd_buf, sizeof(cmd_buf), "./matrix_input matrix_%s.txt", matrix_size);
		printf("%s\n", cmd_buf);
		system(cmd_buf);
		printf("\n\n\n\nI'm done here\n\n\n");
		kill(0, SIGINT);		
	} //end of else
} //end of compare_governor

	

