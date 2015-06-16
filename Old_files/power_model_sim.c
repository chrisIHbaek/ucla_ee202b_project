// ----------------
// For cpu0 only.
// ----------------

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main()
{
	int fd[2]; //to store descriptors

	//create a pipe and store descriptors in fd[0] and fd[1]
	if (pipe(fd) == -1) {
		error("Cannot create a pipe");
	}

	pid_t pid = fork();

	if (pid == -1) {
		fprintf(stderr, "Cannot fork process: %s\n", strerror(errno));
		return 1;
	}

	else if (pid == 0) {
		dup2(fd[1],1); //Set the stdout to the write end of pipe
		close(fd[0]); //Close the read end of pipe

		// This is run dd that will take sufficient time.
//		system("dd if=/dev/zero of=/dev/null count=10000000");
		if(execl("/bin/dd", "bin/dd", "if=/dev/zero", "of=/dev/null", "count=10000000", NULL) == -1) {
			fprintf(stderr, "Cannot run dd: %s\n", strerror(errno));
			return 1;
		}

		
	} //end of else if

	else {
		dup2(fd[0],0); //set stdin to the read end of the pipe.
		close(fd[1]); //close the write end of the pipe.
		
		char line[255];
		
		while(1) {
			printf("Success!\n");
			if (stdin != NULL){
				printf("stdin test\n");
				break;
			}
			
/*
			fgets(line, 255, stdin);
			if (line[0] == '1')
				break;
*/
		}
		printf("while loop ends\n");

/*
		//enable the sensors
		system("echo 1 > /sys/bus/i2c/drivers/INA231/4-0045/enable");

		while(1) {
			//measure voltage and power
			system("echo A7(voltage, power) >> power_model_log.txt");
			system("cat /sys/bus/i2c/drivers/INA231/4-0045/sensor_V >> power_model_log.txt");
			system("cat /sys/bus/i2c/drivers/INA231/4-0045/sensor_W >> power_model_log.txt");
	
			system("echo A15(voltage, power) >> power_model_log.txt");
			system("cat /sys/bus/i2c/drivers/INA231/4-0040/sensor_V >> power_model_log.txt");
			system("cat /sys/bus/i2c/drivers/INA231/4-0040/sensor_V >> power_model_log.txt");
	
			//measure CPU frequency
		}
*/				
	} //end of else
		
	return 0;
}
