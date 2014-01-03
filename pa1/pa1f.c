/* Programming Assignment 1: Exercise F
 * 
 * We are now FINALLY ready to modify the Umix operating system kernel.
 * Up until now, you have studied and modified only user programs that
 * make system calls, but not the kernel.  Here, you will make your first
 * addition to the kernel by implementing the all-important function of
 * context switching.
 * 
 * Whenever Yield (pid) is called, the kernel is entered and eventually
 * calls MySwitchContext (p), which causes a context switch to process p,
 * and returns the process id of the process that just called Yield (pid).
 * This function can be found in the file mykernel1.c, which will contain all
 * of YOUR modifications to the kernel.  If you look at MySwitchContext (p),
 * you will see that it calls yet another function SwitchContext (p), which
 * is an internal kernel function that actually does the context switch, and
 * returns whatever SwitchContext (p) returns.  Without SwitchContext (p),
 * the kernel would not have worked properly up until now, and we needed it
 * to be able to run all the programs shown so far.  In this exercise, you
 * will REMOVE the call to SwitchContext (p), which will break the kernel,
 * and in its place, add your own code to make the kernel work properly again.
 * 
 * MySwitchContext (p) should cause a context switch from the currently
 * running process to process p.  To implement MySwitchContext (p), you
 * are given three utility functions:  SaveContext (), RestoreContext (p),
 * and GetCurProc ().
 * 
 * SaveContext () saves the context of the currently running process (just
 * prior to entering the kernel), storing the state of the CPU registers,
 * including the SP (stack pointer) and lastly the PC (program counter),
 * into a table in the kernel indexed by the pid (which you need not be
 * concerned about).
 *
 * RestoreContext (p) loads the CPU registers with the context that was
 * previously saved for process p.
 *
 * GetCurProc () simply returns the id of the currently running process.
 * 
 * Consider what happens when a process's context is restored.  It begins
 * executing from wherever the PC was pointing to when its state was saved,
 * specifically, somewhere within of SaveContext ().  (In fact, it is saved
 * just before returning from SaveContext - why is this?) Therefore,
 * SaveContext () will return TWICE, even though it was called only once!
 * The first time corresponds to when SaveContext () was actually called,
 * and the second time when the process's context is restored.  YOUR JOB
 * is to find a way of distinguishing between returns so that your code
 * can determine whether or not RestoreContext (p) should be called.
 * (Hint: study the Lecture notes on context switching.  If you
 * understand the notes, you will know how to write this code).
 * 
 * You now have all the tools to implement MySwitchContext (p).  Remove the
 * call to SwitchContext (p) so that the body of MySwitchContext (p) is now
 * empty, and then replace with YOUR code.  The only functions you will need
 * are SaveContext (), RestoreContext (p), and GetCurProc ().  As a hint,
 * you should review how variables get allocated in the data and stack memory
 * areas (and how to effect this via declarations in C, including the use of
 * the keyword "static").  Use variables of minimal scope and lifetime: favor
 * local over global, dynamic over static, automatic over non-automatic.
 * (Think about why this is important, especially for a large complex program
 * like an operating system where many programmers may eventually modify it).
 * Also, you should NOT make any system calls from within MySwitchContext (p),
 * since system calls are called by processes from outside the kernel, and
 * MySwitchContext (p) is called from inside the kernel.
 *
 * Finally, make sure that MySwitchContext (p) returns the proper value.
 * Getting this right is a bit tricky!  Make sure the output using your version
 * of MySwitchContext (p) matches the output of the original unmodified
 * MySwitchContext (p), INCLUDING output based on the return value.
 *
 * You should test your kernel by seeing if it will work with the program
 * below, as well as other test cases you design.  You should test it
 * thoroughly, as it will be graded by seeing if it successfully runs with
 * other test programs (not available to you).
 * 
 * Good luck!
 */

#include <stdio.h>
#include "aux.h"
#include "umix.h"

#define NUMPROCS 3

void handoff (int p);

void Main ()
{
	int i, p, c, r;

	for (i = 0, p = Getpid (); i < NUMPROCS; i++, p = c) {
		Printf ("%d about to fork\n", Getpid ());
		if ((c = Fork ()) == 0) {
			Printf ("%d starting\n", Getpid ());
			handoff (p);
			Printf ("%d exiting\n", Getpid ());
			Exit (0);
		}
		Printf ("%d just forked %d\n", Getpid (), c);
	}

	Printf ("%d yielding to %d\n", Getpid (), c);
	r = Yield (c);
	Printf ("%d resumed by %d, yielding to %d\n", Getpid (), r, c);
	Yield (c);
	Printf ("%d exiting\n", Getpid ());
}

void handoff (p)
	int p;
{
	int r;

	Printf ("%d yielding to %d\n", Getpid (), p);
	r = Yield (p);
	Printf ("%d resumed by %d, yielding to %d\n", Getpid (), r, p);

	Yield (p);
}
