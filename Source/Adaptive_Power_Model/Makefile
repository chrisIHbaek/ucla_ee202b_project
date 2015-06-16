all: print_parameter energy_prediction power_energy_measurement

print_parameter: adaptive_power_model.o
	gcc -o print_parameter adaptive_power_model.o
adaptive_power_model.o: adaptive_power_model.c
	gcc -c adaptive_power_model.c

energy_prediction: energy_prediction.o
	gcc -o energy_prediction energy_prediction.o
energy_prediction.o: energy_prediction.c
	gcc -c energy_prediction.c

power_energy_measurement: power_energy_measurement_low_precision.o
	gcc -o power_energy_measurement power_energy_measurement_low_precision.o
power_energy_measurement_low_precision.o: power_energy_measurement_low_precision.c
	gcc -c power_energy_measurement_low_precision.c