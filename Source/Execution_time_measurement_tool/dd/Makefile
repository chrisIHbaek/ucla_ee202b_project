all: time_measurement_tool dd_program

time_measurement_tool: automatic_execution_time_only.o
	gcc -o time_measurement_tool automatic_execution_time_only.o
automatic_execution_time_only.o: automatic_execution_time_only.c
	gcc -c automatic_execution_time_only.c

dd_program: dd_program.o
	gcc -o dd_program dd_program.o
dd_program.o: dd_program.c
	gcc -c dd_program.c