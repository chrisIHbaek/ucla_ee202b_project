all: time_measurement_tool matrix_input

time_measurement_tool: automatic_execution_time_only.o
	gcc -o time_measurement_tool automatic_execution_time_only.o
automatic_execution_time_only.o: automatic_execution_time_only.c
	gcc -c automatic_execution_time_only.c

matrix_input: Matrix_accept_input.o
	g++ -o matrix_input Matrix_accept_input.o
Matrix.o: Matrix.cpp
	g++ -c Matrix_accept_input.cpp