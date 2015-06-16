#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
	execl("/bin/dd", "bin/dd", "if=/dev/zero", "of=/dev/null", "count=10000000", NULL);
	return 0;
}
