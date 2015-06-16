#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <math.h>

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

void big_CPU_aC();
void little_CPU_aC();
void power_model();
void execution_time_model(int);

int main(int arc, char* argv[]) {
	//Turn off CPU1,2,3
	system("echo 0 > /sys/devices/system/cpu/cpu1/online");
	system("echo 0 > /sys/devices/system/cpu/cpu2/online");
	system("echo 0 > /sys/devices/system/cpu/cpu3/online");

	if (arc < 3) {
		fprintf(stderr, "Need more arguments: %s\n", strerror(errno));
		return 1;	
	}

	int count = atoi(argv[1]);
	double seconds_QoS = atof(argv[2]);
	int i_QoS = 0; //the index for the minimum execution time according to QoS
	int i;

	//estimate execution time for each frequency
	execution_time_model(count/100000); //the input is scaled by 10^5

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
		printf("Execution time: %fs\t", exe_t_array[i]);
		printf("Power: %fW\t\t", rough_power);
		printf("Energy: %f Watt-second for %dMHz\n", energy_array[i], freq_set_MHz[i]);
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
	//Continue on the real-time frequency scaling!!
	return 0;
}

void execution_time_model(int x) { //the count x*10^5
	exe_t_array[0]=0.472*x+0.361;    //250MHz
	exe_t_array[1]=0.3965*x+0.0637;  //300MHz
	exe_t_array[2]=0.342*x+0.108;    //350MHz
	exe_t_array[3]=0.2958*x+0.0424;  //400MHz
	exe_t_array[4]=0.262*x+0.165;    //450MHz
	exe_t_array[5]=0.2413*x-0.0704;  //500MHz
	exe_t_array[6]=0.2134*x+0.0862;  //550MHz
	exe_t_array[7]=0.195*x+0.132;    //600MHz
	exe_t_array[8]=0.235*x+0.101;    //800MHz
	exe_t_array[9]=0.207*x+0.118;   //900MHz
	exe_t_array[10]=0.187*x+0.102;   //1000MHz
	exe_t_array[11]=0.1703*x+0.0288; //1100MHz
	exe_t_array[12]=0.1542*x+0.0759; //1200MHz
	exe_t_array[13]=0.1447*x+0.0667; //1300MHz
	exe_t_array[14]=0.1333*x+0.0733; //1400MHz
	exe_t_array[15]=0.12586*x+0.00929; //1500MHz
	exe_t_array[16]=0.11718*x-0.00767; //1600MHz
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
	

