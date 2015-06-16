all: power_measurement_tool power_auto matrix dd_program

power_measurement_tool: automatic_data_exclude_idle_time.o 
	gcc -o power_measurement_tool automatic_data_exclude_idle_time.o
automatic_data_exclude_idle_time.o: automatic_data_exclude_idle_time.c
	gcc -c automatic_data_exclude_idle_time.c

power_auto: power_model_accept_microsecond.o
	gcc -o power_auto power_model_accept_microsecond.o
power_model_accept_microsecond.o: power_model_accept_microsecond.c
	gcc -c power_model_accept_microsecond.c

matrix: Matrix.o
	g++ -o matrix Matrix.o
Matrix.o: Matrix.cpp
	g++ -c Matrix.cpp

dd_program: dd_program.o
	gcc -o dd_program dd_program.o
dd_program.o: dd_program.c
	gcc -c dd_program.c