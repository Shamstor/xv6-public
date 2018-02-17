#include "param.h"
#include "types.h"
#include "stat.h"
#include "fs.h"
#include "fcntl.h"
#include "syscall.h"
#include "traps.h"
#include "memlayout.h"
#include "user.h"

int main(int argc, char *argv[])
{
	
	int PScheduler(void);

  	printf(0, "\n This program tests the correctness of your lab#2\n");
  
	PScheduler();
	return 0;
 }
  
    
int PScheduler(void){
		 

	int pid;
	int i,j,k;
  
  	printf(1, "\n  Step 2: testing the priority scheduler and setpriority(int priority)) systema call:\n");
    	printf(1, "\n  Step 2: Assuming that the priorities range between range between 0 to 31\n");
    	printf(1, "\n  Step 2: 0 is the highest priority. All processes have a default priority of 10\n");
    	printf(1, "\n  Step 2: The parent processes will switch to priority 0\n");
    	setpriority(0);
    	for (i = 0; i <  3; i++) {
		pid = fork();
		if (pid > 0 ) {
			continue;
		}
		else if ( pid == 0) {
			setpriority(15-10*i);		// og: 30 - 10*i	
			for (j=0;j<50000;j++) {
				for(k=0;k<10000;k++) {
					asm("nop"); 
				}
			}
			printf(1, "\n child# %d with priority %d has finished! \n",getpid(),30-10*i);		


			exit(0);						//	CHANGED THIS FROM exit() TO exit(0)
        	}
        	else {
			printf(2," \n Error \n");
			
        	}
	}

	if(pid > 0) {
		for (i = 0; i <  3; i++) {

			//	CHANGED FROM wait() TO wait(&pid)
			wait(&pid);


		}
                printf(1,"\n if processes with highest priority finished first then its correct \n");
	}
	
	exit(0);		
	//return 0;
}
