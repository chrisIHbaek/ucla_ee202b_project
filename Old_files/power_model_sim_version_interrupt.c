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
	//system("echo bye >> power_model_log.txt");
	exit(1);
}

int main()
{
	pid_t pid = fork();

	if (pid == -1) {
		fprintf(stderr, "Cannot fork process: %s\n", strerror(errno));
		return 1;
	}

	else if (pid == 0) {
		// This is run dd that will take sufficient time.
//		system("dd if=/dev/zero of=/dev/null count=10000000");
		if(execl("/bin/dd", "bin/dd", "if=/dev/zero", "of=/dev/null", "count=10000000", NULL) == -1) {
			fprintf(stderr, "Cannot run dd: %s\n", strerror(errno));
			return 1;
		}

		
	} //end of else if

	else {
		signal(SIGINT, &do_when_interrupted); 

		system("echo Measuring... > power_model_log.txt");

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

		struct timeval tv;
		gettimeofday(&tv, NULL);
		time_t start_time_s = tv.tv_sec; //seconds since 1970-01-01 00:00 UTC.
		time_t time_at_measurement_s;
		suseconds_t start_time_u = tv.tv_usec; //microseconds since 1970-01-01 00:00 UTC.
		suseconds_t time_at_measurement_u;

		//open power_model_log.txt to write (append).
		FILE *f = fopen("power_model_log.txt", "a");

		if (f == NULL) {
			fprintf(stderr, "Error opening!");
			exit(1);
		}

		while(isrunning) {
			//Put timestamp
			gettimeofday(&tv, NULL);
			time_at_measurement_s = tv.tv_sec;
			time_at_measurement_u = tv.tv_usec;
			fprintf(f, "Elapsed time: %ld.%06ld seconds\n", 
					time_at_measurement_s - start_time_s, 
					time_at_measurement_u - start_time_u);

  			//measure voltage and power
			//open sensor readings (read).
			FILE *freq = fopen("/sys/devices/system/cpu/cpu0/cpufreq/scaling_cur_freq", "r");
			FILE *a7_v = fopen("/sys/bus/i2c/drivers/INA231/4-0045/sensor_V", "r");
			FILE *a7_w = fopen("/sys/bus/i2c/drivers/INA231/4-0045/sensor_W", "r");
			FILE *a15_v = fopen("/sys/bus/i2c/drivers/INA231/4-0040/sensor_V", "r");
			FILE *a15_w = fopen("/sys/bus/i2c/drivers/INA231/4-0040/sensor_W", "r");
			if (freq == NULL || a7_v == NULL || a7_w == NULL || a15_v == NULL || a15_w == NULL) {
				fprintf(stderr, "Error opening!");
				exit(1);
			}
			
			fprintf(f, "CPU (cpu0) frequency(MHz): ");
			fscanf(freq, "%s", freq_val);
			freq_val_int = atoi(freq_val)/1000;
			fprintf(f, "%d\n", freq_val_int);

			fprintf(f, "A7 voltage(V), power(W): ");
			fscanf(a7_v, "%s", a7_v_val);
			fscanf(a7_w, "%s", a7_w_val);
			fprintf(f, "%s, %s\n", a7_v_val, a7_w_val);

			fprintf(f, "A15 voltage(V), power(W): ");
			fscanf(a15_v, "%s", a15_v_val);
			fscanf(a15_w, "%s", a15_w_val);
			fprintf(f, "%s, %s\n\n", a15_v_val, a15_w_val);			
			
/*
			system("echo 'A7(voltage, power)' >> power_model_log.txt");
			system("cat /sys/bus/i2c/drivers/INA231/4-0045/sensor_V >> power_model_log.txt");
			system("cat /sys/bus/i2c/drivers/INA231/4-0045/sensor_W >> power_model_log.txt");
	
			system("echo 'A15(voltage, power)' >> power_model_log.txt");
			system("cat /sys/bus/i2c/drivers/INA231/4-0040/sensor_V >> power_model_log.txt");
			system("cat /sys/bus/i2c/drivers/INA231/4-0040/sensor_W >> power_model_log.txt");
*/			
			if (n == 150) 
				isrunning = 0;

			n++;
			usleep(100*1000); //sleep for 0.1 seconds
			//measure CPU frequency
		} //end of while loop
		printf("I'm outside the loop!\n");	
		fclose(f);		

	} //end of else
		
	return 0;
}
