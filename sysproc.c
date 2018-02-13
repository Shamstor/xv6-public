#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{

	int status;
	argint(0, &status);
	exit(status);


  //exit(0);
  return 0;  // not reached
}

int
sys_wait(void)
{

	int* status;
	//	Cast the integer value of status to a char**
	if (argptr(0, (char**)&status, sizeof(*status)) < 0) {
		return -1;
	}
	return wait(status);



  //return wait(0);
}

/*	Added sys_waitpid to sysproc.c and syscall.c and syscall.h
 */
int
sys_waitpid(void)
{

	//	Fetch the pid
	int pid;
	int* status;
	int options;

	//	If error
	if (argint(0, &pid) < 0 || argptr(1, (char**)&status, sizeof(*status)) < 0
		|| argint(2, &options) < 0) {
		return -1;
	}

	return waitpid(pid, status, options);
}



/*	Lab 2:
 *	Add int sys_setPriority(void)
 *	Return -1 if error
 *
 *	Update in syscall.c and syscall.h
 */
int
sys_setpriority(void)
{

	int prior;
	argint(0, &prior);	// Fetch prior from top of user stack
	
	return setpriority(prior);
	//return 0;
}








int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
