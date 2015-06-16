#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	char buf[1024];

	if (argc != 2) {
		fprintf(stderr, "Wrong number of arguments!");
		exit(1);
	}

	snprintf(buf, sizeof(buf), "count=%s", argv[1]);

	execl("/bin/dd", "bin/dd", "if=/dev/zero", "of=/dev/null", buf, NULL);
	return 0;
}
