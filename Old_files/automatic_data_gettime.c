#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>

char* getTime(char* date_to_return) 
{
//    char cBuffer[100];
    time_t zaman;
    struct tm *ltime;
    static struct timeval _t;
    static struct timezone tz;

    time(&zaman);
    ltime = (struct tm *) localtime(&zaman);
    gettimeofday(&_t, &tz);

    strftime(date_to_return,40,"%d.%m.%y %H:%M:%S",ltime);
    sprintf(date_to_return, "%s", date_to_return);

//    printf(" %s \n",cBuffer);

    return date_to_return;
}

int main(int argc, char* argv[]) {
	if (argc != 2) {
		fprintf(stderr, "Wrong number of arguments: %s\n", strerror(errno));
		return 1;	
	}

	char* freq_set[] = {"250MHz", "300MHz", "350MHz", "400MHz", "450MHz", 
			"500MHz", "550MHz", "600MHz", "800MHz", "900MHz",
			"1000MHz", "1.10GHz", "1.20GHz", "1.30GHz", "1.40GHz", "1.50GHz", "1.60GHz"};

	int i; //for loop index
	struct stat st = {0}; //to check if a directory exists
	char *date_to_return = malloc (sizeof (char) * 100);

	FILE* f = fopen("execution_time_log.txt","w");
	fclose(f);

	for (i=0;i<17;i++) {
		//printf("here %s\n", freq_set[i]);
		char buf[1024];
		system("cpufreq-set -g userspace");
		snprintf(buf, sizeof(buf), "cpufreq-set -f '%s'", freq_set[i]);
		system(buf);
		//system("cpufreq-info | grep asserted");

		char program2run[1024];
		snprintf(program2run, sizeof(program2run), "./execution_time '%s'", argv[1]);
		system(program2run);


	}

	//check if exeuction_time_log directory exists, if not create one.
	if (stat("./execution_time_log", &st) == -1) {
    		mkdir("./execution_time_log", 0700);
	}

	char* date = getTime(date_to_return);
	free(date_to_return);

	//Copy the execution_time_log.txt
	char cp_command[1024];
	snprintf(cp_command, sizeof(cp_command), "cp execution_time_log.txt ./execution_time_log/'%s'_log.txt", date);
	system(cp_command);
	return 0;
}
