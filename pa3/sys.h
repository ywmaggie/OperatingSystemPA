/*	Umix kernel-related major constants and interfaces
 *
 *	Relevant only to kernel code (i.e., NOT to user processes).
 *
 *      The constants should NOT to be changed, unless explicitly stated
 *      otherwise, as other already-compiled parts of the kernel rely on
 *      these constants.
 */

#include <setjmp.h>

/*	Processes
 */
#define MAXPROCS	10	/* max processes: DO NOT CHANGE */

/*	Shared Memory
 */
#define MAXSHM		1024	/* max shared memory size (bytes): DO NOT CHANGE */

/*	Semaphores
 */
#define MAXSEMS		100	/* max semaphores: DO NOT CHANGE */

/*	Scheduling
 */
#define NOSCHEDPOLICY	0
#define ARBITRARY	1
#define FIFO		2
#define LIFO		3
#define ROUNDROBIN	4
#define PROPORTIONAL	5

/*	Kernel procedures: can only be called from within the kernel
 */

/*	Context switching
*/
void SaveContext ();		/* save the calling process's context */
void RestoreContext (int p);	/* restore the context of process p */
int SwitchContext (int p);	/* working version of switch context */
int GetCurProc ();		/* returns current process's id */

/*	Scheduling
*/
void SetTimer (int t);		/* timer to interrupt after t ticks */
int GetTimer ();		/* returns the current value of timer */
int Block (int p);		/* make proc p ineligible for sched */
int Unblock (int p);		/* make proc p eligible for sched */
int SetSchedPolicy (int p);	/* set the scheduling policy to p */
int GetSchedPolicy ();		/* return the scheduling policy */
void DoSched ();		/* make sched decision at next opportune time */

/*	Other
 */
void Panic (char *s);		/* causes abnormal exit from kernel */
