/* mykernel2.c: your portion of the kernel (last modified 10/18/09)
 *
 *	Below are procedures that are called by other parts of the kernel.
 *	Your ability to modify the kernel is via these procedures.  You may
 *	modify the bodies of these procedures any way you wish (however,
 *	you cannot change the interfaces).
 * 
 */

#include "aux.h"
#include "sys.h"
#include "mykernel2.h"

#define TIMERINTERVAL 100	/* in ticks (tick = 10 msec) */
#define MAXRATIO 10000000

/*	A sample process table.  You may change this any way you wish.
 */

static struct {
	int valid;		/* is this entry valid: 1 = yes, 0 = no */
	int pid;		/* process id (as provided by kernel) */
    int runningTime;
    int aliveTime;
    float utilization;
    float requested;
    float ratio;
    int next;
} proctab[MAXPROCS];

static int head;
static int tail;
static int run_proc;
static int next_proc;
static float CurrUtil;

void ReAllocate();

/*	InitSched () is called when kernel starts up.  First, set the
 *	scheduling policy (see sys.h).  Make sure you follow the rules
 *	below on where and how to set it.  Next, initialize all your data
 *	structures (such as the process table).  Finally, set the timer
 *	to interrupt after a specified number of ticks.
 */

void InitSched ()
{
	int i;
    //Printf("MAXPROCS:%d\n",MAXPROCS);
	/* First, set the scheduling policy.  You should only set it
	 * from within this conditional statement.  While you are working
	 * on this assignment, GetSchedPolicy will return NOSCHEDPOLICY,
	 * and so the condition will be true and you may set the scheduling
	 * policy to whatever you choose (i.e., you may replace ARBITRARY).
	 * After the assignment is over, during the testing phase, we will
	 * have GetSchedPolicy return the policy we wish to test, and so
	 * the condition will be false and SetSchedPolicy will not be
	 * called, thus leaving the policy to whatever we chose to test.
	 */
	if (GetSchedPolicy () == NOSCHEDPOLICY) {	/* leave as is */
		SetSchedPolicy (FIFO);		/* set policy here */
	}
		
	/* Initialize all your data structures here */
	for (i = 0; i < MAXPROCS; i++) {
		proctab[i].valid = 0;
        proctab[i].runningTime = 0;
        proctab[i].aliveTime = 0;
        proctab[i].utilization = 0;
        proctab[i].requested = 0;
        proctab[i].ratio = 0;
        proctab[i].next = -1;
	}

	/* Set the timer last */
	SetTimer (TIMERINTERVAL);
}


/*	StartingProc (pid) is called by the kernel when the process
 *	identified by pid is starting.  This allows you to record the
 *	arrival of a new process in the process table, and allocate
 *	any resources (if necessary).  Returns 1 if successful, 0 otherwise.
 */

int StartingProc (pid)
	int pid;
{
	int i;
    int IsEmpty;
   Printf("StartingProc entered for pid %d\n", pid); 
	if (proctab[head].valid == 0) {
        IsEmpty = 1;
        head = 0;
        tail = 0;
    }
    else IsEmpty = 0;

	for (i = 0; i < MAXPROCS; i++) {
        Printf("%d:pid %d; valid flag %d\n",i,proctab[i].pid, proctab[i].valid);
		if (! proctab[i].valid) {
			proctab[i].valid = 1;
			proctab[i].pid = pid;
            proctab[tail].next = i;
            proctab[i].next = -1;
            tail = i;
            if (GetSchedPolicy () == LIFO && ! IsEmpty) {
                DoSched();
            }
			return (1);
		}
	}

	Printf ("Error in StartingProc: no free table entries\n");
	return (0);
}
			

/*	EndingProc (pid) is called by the kernel when the process
 *	identified by pid is ending.  This allows you to update the
 *	process table accordingly, and deallocate any resources (if
 *	necessary).  Returns 1 if successful, 0 otherwise.
 */


int EndingProc (pid)
	int pid;
{
	int i;
    int prev;
    
    i = head;
    if (proctab[i].valid && proctab[i].pid == pid){
        head = proctab[i].next;
        proctab[i].valid = 0;
        CurrUtil -= proctab[i].requested;
        return(1);
    }
    prev = i;
    i = proctab[i].next;
    
    while (proctab[i].valid){
        if (proctab[i].pid == pid) {
            proctab[i].valid=0;
            proctab[prev].next = proctab[i].next;
            if (i == tail) {
                tail = prev;
            }
            CurrUtil -= proctab[i].requested;
            ReAllocate();
            return(1);
        }
        prev = i;
        i = proctab[i].next;
    }
    
	/*for (i = 0; i < MAXPROCS; i++) {
		if (proctab[i].valid && proctab[i].pid == pid) {
			proctab[i].valid = 0;
			return (1);
		}
	}*/

	Printf ("Error in EndingProc: can't find process %d\n", pid);
	return (0);
}


/*	SchedProc () is called by kernel when it needs a decision for
 *	which process to run next.  It calls the kernel function
 *	GetSchedPolicy () which will return the current scheduling policy
 *	which was previously set via SetSchedPolicy (policy). SchedProc ()
 *	should return a process id, or 0 if there are no processes to run.
 */

int SchedProc ()
{
	int i;
    int minProcReqCPU = -1;
    int minProcNoReqCPU = -1;
    float minUtilization = 2;
    float minRatio = MAXRATIO;
    
    static int s;
    
	switch (GetSchedPolicy ()) {

	case ARBITRARY:

            for (i = 0; i < MAXPROCS; i++) {
                if (proctab[i].valid) {
                    return (proctab[i].pid);
                }
            }
            break;

	case FIFO:
            
            if (proctab[head].valid) {
                return (proctab[head].pid);
            }
            break;

	case LIFO:

            if (proctab[head].valid) {
                return (proctab[tail].pid);
            }
            break;

	case ROUNDROBIN:
            
            if (next_proc == -1) {
                next_proc = head;
            }
            if (proctab[next_proc].valid) {
                run_proc = next_proc;
                next_proc = proctab[run_proc].next;
                return (proctab[run_proc].pid);
            }
            break;

	case PROPORTIONAL:
            
            
            for (i = 0; i < MAXPROCS; i++) {
                if (proctab[i].valid) {
                    if (proctab[i].requested == 0) {
                        if (proctab[i].utilization < minUtilization) {
                            minProcNoReqCPU = i;
                            minUtilization = proctab[i].utilization;
                        }
                    }
                    else{
                        if (proctab[i].ratio < minRatio) {
                            minProcReqCPU = i;
                            minRatio = proctab[i].ratio;
                        }
                    }
                }
            }
            //Printf("pid %d minUtilization %f \n",proctab[minProcNoReqCPU].pid,minUtilization);

            if (minRatio < 1) {
                proctab[minProcReqCPU].runningTime += 1;
                return (proctab[minProcReqCPU].pid);
            }
            else if(minProcReqCPU != -1 && minProcNoReqCPU == -1){
                proctab[minProcReqCPU].runningTime += 1;
                return (proctab[minProcReqCPU].pid);
            }
            else if(minProcNoReqCPU != -1){
                proctab[minProcNoReqCPU].runningTime += 1;
                return (proctab[minProcNoReqCPU].pid);
            }
            else{
                break;
            }

	}
	
	return (0);
}


/*	HandleTimerIntr () is called by the kernel whenever a timer
 *	interrupt occurs.
 */

void HandleTimerIntr ()
{
	int i;
    SetTimer (TIMERINTERVAL);
    
    for (i = 0; i < MAXPROCS; i++) {
		if (proctab[i].valid) {
			proctab[i].aliveTime += 1;
            proctab[i].utilization = 1.0*proctab[i].runningTime/proctab[i].aliveTime;
            if (proctab[i].requested) {
                proctab[i].ratio = proctab[i].utilization/proctab[i].requested;
            }
            //Printf("requested:%f util:%f  ratio:%f\n",proctab[i].requested,proctab[i].utilization,proctab[i].ratio);
		}
	}

	switch (GetSchedPolicy ()) {	/* is policy preemptive? */

	case ROUNDROBIN:		/* ROUNDROBIN is preemptive */
	case PROPORTIONAL:		/* PROPORTIONAL is preemptive */

		DoSched ();		/* make scheduling decision */
		break;

	default:			/* if non-preemptive, do nothing */
		break;
	}
}

/*	MyRequestCPUrate (pid, m, n) is called by the kernel whenever a process
 *	identified by pid calls RequestCPUrate (m, n).  This is a request for
 *	a fraction m/n of CPU time, effectively running on a CPU that is m/n
 *	of the rate of the actual CPU speed.  m of every n quantums should
 *	be allocated to the calling process.  Both m and n must be greater
 *	than zero, and m must be less than or equal to n.  MyRequestCPUrate
 *	should return 0 if successful, i.e., if such a request can be
 *	satisfied, otherwise it should return -1, i.e., error (including if
 *	m < 1, or n < 1, or m > n).  If MyRequestCPUrate fails, it should
 *	have no effect on scheduling of this or any other process, i.e., as
 *	if it were never called.
 */

int MyRequestCPUrate (pid, m, n)
	int pid;
	int m;
	int n;
{
    int i;
    
    for (i = 0; i < MAXPROCS; i++) {
		if (proctab[i].valid && proctab[i].pid == pid) {
            if(proctab[i].requested == 0){
                if (m < 1 || n < 1 || m>n || CurrUtil + 1.0*m/n >1){
                    return (-1);
                }
                proctab[i].requested = 1.0*m/n;
                CurrUtil += 1.0*m/n;
                ReAllocate();
                return (0);
            }
            else{
                if(m < 1 || n < 1 || m>n || CurrUtil - proctab[i].requested + 1.0*m/n >1){
                    return(-1);
                }
                proctab[i].requested = 1.0*m/n;
                CurrUtil = CurrUtil - proctab[i].requested + 1.0*m/n;
                ReAllocate();
                return (0);
            }
		}
	}
    return (-1);
}

void ReAllocate(){
    int i;
    for (i = 0; i < MAXPROCS; i++){
        proctab[i].runningTime = 0;
        proctab[i].aliveTime = 0;
        proctab[i].utilization = 0;
    }
}

