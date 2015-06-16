#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
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

	//Turn off CPU1,2,3
	system("echo 0 > /sys/devices/system/cpu/cpu1/online");
	system("echo 0 > /sys/devices/system/cpu/cpu2/online");
	system("echo 0 > /sys/devices/system/cpu/cpu3/online");

	//enable the sensors
	system("echo 1 > /sys/bus/i2c/drivers/INA231/4-0045/enable");
	system("echo 1 > /sys/bus/i2c/drivers/INA231/4-0040/enable");

	//get current frequency
	FILE *f_freq = fopen("/sys/devices/system/cpu/cpu0/cpufreq/scaling_cur_freq", "r");

	fscanf(f_freq, "%s", freq_val);
	freq = atoi(freq_val)/1000;

	//If the frequency is greater than 800MHz, it is the big cpu.
	if (freq >= 800) { //Big CPU
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

		//evaluation
		printf("Big CPU\n");
		printf("Frequency: %d MHz\n", freq);
		printf("V^2*freq: %f\n", v2f);
		printf("Power calculated: %f Watts\n", power);
		printf("adjusted power calculated: %f Watts\n", (aC * v2f) - (5.29 * 0.01));
		printf("Power measured: %s Watts\n", a15_w_val);
		printf("Approximate activity factor x capacitance: %f\n", aC);

	} //end of Big CPU

	else { //Little CPU
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
		//evaluation
		printf("Little CPU\n");
		printf("Frequency: %d MHz\n", freq);
		printf("V^2*freq: %f\n", v2f);
		printf("Power calculated: %f Watts\n", power);
		printf("adjusted power calculated: %f Watts\n", (aC * v2f) + (6.534 * 0.00001));
		printf("Power measured: %s Watts\n", a7_w_val);
		printf("Approximate activity factor x capacitance: %f\n", aC);
		
	} //end of Little CPU

	return 0;
}

	
	

