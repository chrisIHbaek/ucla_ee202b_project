#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <math.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>

sig_atomic_t volatile isrunning = 1;

FILE *f_freq; //scaling_cur_frequency file
char freq_val[10];
int freq;
double voltage;
double v2f; //voltage * voltage * frequency
double power;
double power_measured;
double power_measured_sum = 0;

double aC; //activity factor x capacitance
char a7_w_val[10];
char a15_w_val[10];
double exe_t_array[17];
double energy_array[17];
int freq_set_MHz[] = {250, 300, 350, 400, 450, 500, 550, 600, 
	800, 900, 1000, 1100, 1200, 1300, 1400, 1500, 1600};

double compare_governors();
void big_CPU_aC();
void little_CPU_aC();
void power_model();
void execution_time_model(int);

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

	if (arc < 3) {
		fprintf(stderr, "Need more arguments: %s\n", strerror(errno));
		return 1;	
	}

	int matrix_size = atoi(argv[1]);
	double seconds_QoS = atof(argv[2]);
	int i_QoS = 0; //the index for the minimum execution time according to QoS
	int i;

	//estimate execution time for each frequency
	execution_time_model(matrix_size);

	for (i=0; i<17; i++) {
		if (exe_t_array[i] <= seconds_QoS) {
			i_QoS = i;
			break;
		}
		else if (i == 16) {
			printf("No frequency will satisfy QoS!\n");
			printf("Selecting the maximum frequency...\n");
			i_QoS = i;
		}
	} 
	
	double rough_power; //from power model
	double rough_voltage; //from power model
	double big_init_aC = 8.27 * 0.0001; //initial activity * C value is 8.27*10^-4
	double little_init_aC = 1.722 * 0.0001; //initial activity * C is 1.722*10^-4

	//Calculate the energy consumption for each frequency.
	for (i=i_QoS; i<17; i++) {
		if (i <= 7) {//little CPU (up to 600MHz)
			if (i < 3) 
				rough_voltage = 0.95;
			else
				rough_voltage = 1.2 * 0.001 * freq_set_MHz[i] + 0.4765;
			rough_power = (little_init_aC * rough_voltage * rough_voltage * freq_set_MHz[i]) + (6.534 * 0.00001);
		}
		if (i > 7) { //big CPU (800MHz - 1.6GHz)
			rough_voltage = 3.152 * 0.0001 * freq_set_MHz[i] + 0.647287;
			rough_power = (big_init_aC * rough_voltage * rough_voltage * freq_set_MHz[i]) - (5.29 * 0.01);
		}
		energy_array[i] = exe_t_array[i] * rough_power;
		printf("%dMHz\t Execution time: %fs\t", freq_set_MHz[i], exe_t_array[i]);
		printf("Power: %fW\t\t", rough_power);
		printf("Energy: %f Watt-second\n", energy_array[i]);
	}
	
	//Fine the minimum energy
	int location = i_QoS;
	double min_energy = energy_array[i_QoS];
	for (i=i_QoS+1; i<17; i++ ) 
    	{
        	if (energy_array[i] < min_energy ) 
        	{
           		min_energy = energy_array[i];
           		location = i;
        	}
    	} 

	printf("%dMHz will result in least energy consumption!\n", freq_set_MHz[location]);

	if (!strcmp(argv[3], "-g")) { //comparison of governors enabled
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

		signal(SIGINT, &do_when_interrupted);  //To stop the loop with ctr + C

		//enable the sensors
		system("echo 1 > /sys/bus/i2c/drivers/INA231/4-0045/enable");
		system("echo 1 > /sys/bus/i2c/drivers/INA231/4-0040/enable");

		struct timeval tv;
		gettimeofday(&tv, NULL);
		time_t start_time_s = tv.tv_sec; //seconds since 1970-01-01 00:00 UTC.
		time_t time_at_measurement_s;
		suseconds_t start_time_u = tv.tv_usec; //microseconds since 1970-01-01 00:00 UTC.
		suseconds_t time_at_measurement_u;

		while(isrunning) {
			//Put timestamp
			gettimeofday(&tv, NULL);
			time_at_measurement_s = tv.tv_sec;
			time_at_measurement_u = tv.tv_usec;
			printf("Elapsed time: %ld.%06ld seconds\t", 
					time_at_measurement_s - start_time_s, 
					time_at_measurement_u - start_time_u);

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
				printf("Big CPU: %sW\n", a15_w_val);
				energy_sum += 0.1 * atof(a15_w_val);
			}

			else {//Little CPU
				fscanf(file_a7_w, "%s", a7_w_val);
				energy_sum += 0.1 * atof(a7_w_val);
				printf("Little CPU: %sW\n", a7_w_val);
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
		system(cmd_buf);
		kill(0, SIGINT);		
	} //end of else
} //end of compare_governor

void execution_time_model(int x) { //x is the matrix dimension
	exe_t_array[0] = 0.000000326*x*x*x-0.0000252*x*x+0.928; //250MHz
	exe_t_array[1] = 0.000000267*x*x*x-0.0000162*x*x+0.517; //300MHz
	exe_t_array[2] =0.000000237*x*x*x-0.0000206*x*x+0.802;  //350MHz
	exe_t_array[3] =0.000000202*x*x*x-0.0000117*x*x+0.386;	//400MHz
	exe_t_array[4] =0.000000189*x*x*x-0.0000180*x*x+0.636;	//450MHz
	exe_t_array[5] =0.000000169*x*x*x-0.0000138*x*x+0.432;	//500MHz
	exe_t_array[6] =0.000000153*x*x*x-0.0000128*x*x+0.423;	//550MHz
	exe_t_array[7] =0.000000138*x*x*x-0.0000091*x*x+0.283;	//600MHz
	exe_t_array[8] =0.0000000967*x*x*x-0.0000212*x*x+0.739;	//800MHz
	exe_t_array[9] =0.0000000888*x*x*x-0.0000209*x*x+0.717;	//900MHz
	exe_t_array[10] =0.0000000795*x*x*x-0.0000184*x*x+0.661;//1000MHz
	exe_t_array[11] =0.0000000746*x*x*x-0.0000186*x*x+0.667;//1.1GHz
	exe_t_array[12] =0.0000000687*x*x*x-0.0000169*x*x+0.594;//1.2GHz
	exe_t_array[13] =0.0000000639*x*x*x-0.000016*x*x+0.574;	//1.3GHz
	exe_t_array[14] =0.0000000622*x*x*x-0.0000171*x*x+0.607;//1.4GHz
	exe_t_array[15] =0.0000000607*x*x*x-0.0000175*x*x+0.637;//1.5GHz
	exe_t_array[16] =0.0000000557*x*x*x-0.0000158*x*x+0.578;//1.6GHz
} //end of execution_time_model(int)

void power_model() {
	//enable the sensors
	system("echo 1 > /sys/bus/i2c/drivers/INA231/4-0045/enable");
	system("echo 1 > /sys/bus/i2c/drivers/INA231/4-0040/enable");

	//get current frequency
	f_freq = fopen("/sys/devices/system/cpu/cpu0/cpufreq/scaling_cur_freq", "r");

	fscanf(f_freq, "%s", freq_val);
	freq = atoi(freq_val)/1000;

	//If the frequency is greater than 800MHz, it is the big cpu.
	if (freq >= 800) {
		big_CPU_aC();
	}

	else { //Little CPU
		little_CPU_aC();	
	} //end of Little CPU
} //end of power_model

void big_CPU_aC() {
	voltage = 3.152 * 0.0001 * freq + 0.647287;
	aC = 8.27 * 0.0001; //initial activity * C value is 8.27*10^-4
	v2f = voltage * voltage * freq;
	power = (aC * v2f) - (5.29 * 0.01);

	//measure power
	//We do this several times to avoid peaks
	int i;		
	for (i = 0; i<100; i++) {
		//get big cpu power
		FILE *a15_w = fopen("/sys/bus/i2c/drivers/INA231/4-0040/sensor_W", "r");
		fscanf(a15_w, "%s", a15_w_val);
		power_measured = atof(a15_w_val);
		power_measured_sum += power_measured;
	}

	power_measured = power_measured_sum / 100; //Mean of all collected power;

	//Compare with the threshold to determine whether to adjust activity factor or not.
	if (fabs(power_measured-power) > 0.06) { //0.06 is the threshhold
		aC = (power_measured + (5.29 * 0.01)) / v2f;
	}
} //end of big_CPU_aC()

void little_CPU_aC() {
	//The relationship between frequency and voltage varies.
	if (freq < 400) {
		voltage = 0.95;	
	}
	else {
		voltage = 1.2 * 0.001 * freq + 0.4765;
	}
	aC = 1.722 * 0.0001; //initial activity * C is 1.722*10^-4
	v2f = voltage * voltage * freq;		
	power = (aC * v2f) + (6.534 * 0.00001);
	
	int i;		
	for (i = 0; i<100; i++) {
		//get little cpu power
		FILE *a7_w = fopen("/sys/bus/i2c/drivers/INA231/4-0045/sensor_W", "r");
		fscanf(a7_w, "%s", a7_w_val);
		power_measured = atof(a7_w_val);
		power_measured_sum += power_measured;
	}

	power_measured = power_measured_sum / 100; //Mean of all collected power;

	//Compare with the threshold to determine whether to adjust activity factor or not.
	if (fabs(power_measured-power) > 0.006) { //0.006 is the threshhold
		aC = (power_measured - (6.534 * 0.00001)) / v2f;
	}	
} //end of little_CPU_aC()	
	

