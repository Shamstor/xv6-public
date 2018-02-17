#include "param.h"
#include "types.h"
#include "stat.h"
#include "fs.h"
#include "fcntl.h"
#include "syscall.h"
#include "traps.h"
#include "memlayout.h"
#include "user.h"

int main(int argc, char *argv[]) {
	int SchedEx(void);
	printf(0, "\n This program tests the correctness of the bonus part 1\n");

	SchedEx();
	return 0;
}

int SchedEx(void) {

	int pid;
	int i,j,k;

	setpriority(0);
	for (i = 0; i < 3; ++i) {
		pid = fork();
		if (pid == 0) {		// Child doesn't go
			continue;
		}
		else if (pid > 0) {
			setpriority(10 - 5*i);
			for (j = 0; j < 50000; ++j) {
				for (k = 0; k < 10000; k++) {
					asm("nop");
				}
			}
			printf(1, "\n Child# %d with priority %d has finished!\n", getpid(),10-5*i);
			exit(0);
		}
		else {
			printf(2, "\n Error \n");
		}
	}
	
	if (pid > 0) {
		for (i = 0; i < 3; ++i) {
			printf(1, "Current priority before waiting: %d", getpriority(pid));
			wait(&pid);
			printf(1, "Priority after waiting: %d", getpriority(pid));
		}
		printf(1, "\n if processes with highest priority finished first, then its correct \n");
	}
	exit(0);
}



